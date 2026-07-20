import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.offset_parser import PduOffsetEntry


class RubyElixirGeneratorTest(unittest.TestCase):
    def test_generate_all_emits_ruby_and_elixir_types(self):
        message_cache = {
            "geometry_msgs/Vector3": {
                "package": "geometry_msgs",
                "message": "Vector3",
                "fields": [
                    {"name": "x", "type": "float64"},
                    {"name": "y", "type": "float64"},
                    {"name": "z", "type": "float64"},
                ],
            },
            "geometry_msgs/Twist": {
                "package": "geometry_msgs",
                "message": "Twist",
                "fields": [
                    {"name": "linear", "type": "Vector3"},
                    {"name": "angular", "type": "Vector3"},
                    {"name": "labels", "type": "string[]"},
                ],
            },
        }

        with tempfile.TemporaryDirectory() as tmp:
            output_root = Path(tmp)
            CodeGenerator("template").generate_all(message_cache, {}, output_root)

            ruby_twist = output_root / "ruby/geometry_msgs/pdu_type_Twist.rb"
            elixir_twist = output_root / "elixir/geometry_msgs/pdu_type_Twist.ex"

            self.assertTrue(ruby_twist.exists())
            self.assertTrue(elixir_twist.exists())

            ruby_content = ruby_twist.read_text()
            self.assertIn("class Twist", ruby_content)
            self.assertIn("HakoPdu::GeometryMsgs::Vector3.from_h(value)", ruby_content)
            self.assertIn("def self.from_json(json)", ruby_content)

            elixir_content = elixir_twist.read_text()
            self.assertIn("defmodule HakoPdu.GeometryMsgs.Twist do", elixir_content)
            self.assertIn("HakoPdu.GeometryMsgs.Vector3.from_map(value)", elixir_content)
            self.assertIn("def from_json(json) when is_binary(json) do", elixir_content)

            if shutil.which("ruby"):
                subprocess.run(["ruby", "-c", str(ruby_twist)], check=True, capture_output=True, text=True)
            if shutil.which("elixirc"):
                subprocess.run(
                    [
                        "elixirc",
                        "-o",
                        str(output_root / "beam"),
                        str(output_root / "elixir/geometry_msgs/pdu_type_Vector3.ex"),
                        str(elixir_twist),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )

    def test_generates_offset_based_ruby_and_elixir_converters(self):
        message_cache = {
            "geometry_msgs/Vector3": {
                "package": "geometry_msgs",
                "message": "Vector3",
                "fields": [
                    {"name": "x", "type": "float64"},
                    {"name": "y", "type": "float64"},
                    {"name": "z", "type": "float64"},
                ],
            },
            "geometry_msgs/Twist": {
                "package": "geometry_msgs",
                "message": "Twist",
                "fields": [
                    {"name": "linear", "type": "Vector3"},
                    {"name": "angular", "type": "Vector3"},
                ],
            },
            "geometry_msgs/Vector3Array": {
                "package": "geometry_msgs",
                "message": "Vector3Array",
                "fields": [
                    {"name": "points", "type": "Vector3[]"},
                    {"name": "weights", "type": "float64[]"},
                ],
            },
        }
        vector3_offsets = [
            PduOffsetEntry("single", "primitive", "x", "float64", 0, 8, 1),
            PduOffsetEntry("single", "primitive", "y", "float64", 8, 8, 1),
            PduOffsetEntry("single", "primitive", "z", "float64", 16, 8, 1),
        ]
        twist_offsets = [
            PduOffsetEntry("single", "struct", "linear", "Vector3", 0, 24, 1),
            PduOffsetEntry("single", "struct", "angular", "Vector3", 24, 24, 1),
        ]
        vector3_array_offsets = [
            PduOffsetEntry("varray", "struct", "points", "Vector3", 0, 24, 1),
            PduOffsetEntry("varray", "primitive", "weights", "float64", 8, 8, 1),
        ]

        with tempfile.TemporaryDirectory() as tmp:
            output_root = Path(tmp)
            generator = CodeGenerator("template")
            generator.generate_all(message_cache, {}, output_root)
            generator.generate_ruby_converter(message_cache["geometry_msgs/Vector3"], vector3_offsets, output_root)
            generator.generate_ruby_converter(message_cache["geometry_msgs/Twist"], twist_offsets, output_root)
            generator.generate_ruby_converter(message_cache["geometry_msgs/Vector3Array"], vector3_array_offsets, output_root)
            generator.generate_elixir_converter(message_cache["geometry_msgs/Vector3"], vector3_offsets, output_root)
            generator.generate_elixir_converter(message_cache["geometry_msgs/Twist"], twist_offsets, output_root)
            generator.generate_elixir_converter(message_cache["geometry_msgs/Vector3Array"], vector3_array_offsets, output_root)

            ruby_conv = output_root / "ruby/geometry_msgs/pdu_conv_Twist.rb"
            ruby_array_conv = output_root / "ruby/geometry_msgs/pdu_conv_Vector3Array.rb"
            elixir_conv = output_root / "elixir/geometry_msgs/pdu_conv_Twist.ex"
            elixir_array_conv = output_root / "elixir/geometry_msgs/pdu_conv_Vector3Array.ex"

            self.assertTrue(ruby_conv.exists())
            self.assertTrue(ruby_array_conv.exists())
            self.assertTrue(elixir_conv.exists())
            self.assertTrue(elixir_array_conv.exists())
            self.assertIn("ruby_to_pdu_twist", ruby_conv.read_text())
            self.assertIn("pdu_to_elixir_twist", elixir_conv.read_text())
            self.assertIn("ruby_to_pdu_vector3_array", ruby_array_conv.read_text())
            self.assertIn("pdu_to_elixir_vector3_array", elixir_array_conv.read_text())

            if shutil.which("ruby"):
                subprocess.run(["ruby", "-c", str(ruby_conv)], check=True, capture_output=True, text=True)
                subprocess.run(
                    [
                        "ruby",
                        f"-I{output_root / 'ruby'}",
                        "-e",
                        (
                            "require 'geometry_msgs/pdu_conv_Twist';"
                            "v=HakoPdu::GeometryMsgs::Vector3.new(x: 1.0, y: 2.0, z: 3.0);"
                            "w=HakoPdu::GeometryMsgs::Vector3.new(x: 4.0, y: 5.0, z: 6.0);"
                            "t=HakoPdu::GeometryMsgs::Twist.new(linear: v, angular: w);"
                            "bin=HakoPdu::GeometryMsgs::TwistConverter.ruby_to_pdu_twist(t);"
                            "out=HakoPdu::GeometryMsgs::TwistConverter.pdu_to_ruby_twist(bin);"
                            "raise unless out.linear.x == 1.0 && out.angular.z == 6.0 && bin.bytesize == 72"
                        ),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )
                subprocess.run(
                    [
                        "ruby",
                        f"-I{output_root / 'ruby'}",
                        "-e",
                        (
                            "require 'geometry_msgs/pdu_conv_Vector3Array';"
                            "a=HakoPdu::GeometryMsgs::Vector3.new(x: 1.0, y: 2.0, z: 3.0);"
                            "b=HakoPdu::GeometryMsgs::Vector3.new(x: 4.0, y: 5.0, z: 6.0);"
                            "obj=HakoPdu::GeometryMsgs::Vector3Array.new(points: [a,b], weights: [7.0,8.0]);"
                            "bin=HakoPdu::GeometryMsgs::Vector3ArrayConverter.ruby_to_pdu_vector3_array(obj);"
                            "out=HakoPdu::GeometryMsgs::Vector3ArrayConverter.pdu_to_ruby_vector3_array(bin);"
                            "raise unless out.points.length == 2 && out.points[1].z == 6.0 && out.weights == [7.0,8.0] && bin.bytesize == 104;"
                            "empty=HakoPdu::GeometryMsgs::Vector3Array.new;"
                            "empty_bin=HakoPdu::GeometryMsgs::Vector3ArrayConverter.ruby_to_pdu_vector3_array(empty);"
                            "empty_out=HakoPdu::GeometryMsgs::Vector3ArrayConverter.pdu_to_ruby_vector3_array(empty_bin);"
                            "raise unless empty_out.points == [] && empty_out.weights == [] && empty_bin.bytesize == 40"
                        ),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )

            if shutil.which("elixirc") and shutil.which("elixir"):
                beam_dir = output_root / "beam"
                subprocess.run(
                    [
                        "elixirc",
                        "-o",
                        str(beam_dir),
                        str(output_root / "elixir/geometry_msgs/pdu_type_Vector3.ex"),
                        str(output_root / "elixir/geometry_msgs/pdu_type_Twist.ex"),
                        str(output_root / "elixir/geometry_msgs/pdu_type_Vector3Array.ex"),
                        str(output_root / "elixir/geometry_msgs/pdu_conv_Vector3.ex"),
                        str(elixir_conv),
                        str(elixir_array_conv),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )
                subprocess.run(
                    [
                        "elixir",
                        "-pa",
                        str(beam_dir),
                        "-e",
                        (
                            "v = HakoPdu.GeometryMsgs.Vector3.new(%{x: 1.0, y: 2.0, z: 3.0});"
                            "w = HakoPdu.GeometryMsgs.Vector3.new(%{x: 4.0, y: 5.0, z: 6.0});"
                            "t = HakoPdu.GeometryMsgs.Twist.new(%{linear: v, angular: w});"
                            "bin = HakoPdu.GeometryMsgs.TwistConverter.elixir_to_pdu_twist(t);"
                            "out = HakoPdu.GeometryMsgs.TwistConverter.pdu_to_elixir_twist(bin);"
                            "unless out.linear.x == 1.0 and out.angular.z == 6.0 and byte_size(bin) == 72, do: raise(\"bad roundtrip\")"
                        ),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )
                subprocess.run(
                    [
                        "elixir",
                        "-pa",
                        str(beam_dir),
                        "-e",
                        (
                            "a = HakoPdu.GeometryMsgs.Vector3.new(%{x: 1.0, y: 2.0, z: 3.0});"
                            "b = HakoPdu.GeometryMsgs.Vector3.new(%{x: 4.0, y: 5.0, z: 6.0});"
                            "obj = HakoPdu.GeometryMsgs.Vector3Array.new(%{points: [a, b], weights: [7.0, 8.0]});"
                            "bin = HakoPdu.GeometryMsgs.Vector3ArrayConverter.elixir_to_pdu_vector3_array(obj);"
                            "out = HakoPdu.GeometryMsgs.Vector3ArrayConverter.pdu_to_elixir_vector3_array(bin);"
                            "unless length(out.points) == 2 and Enum.at(out.points, 1).z == 6.0 and out.weights == [7.0, 8.0] and byte_size(bin) == 104, do: raise(\"bad varray roundtrip\");"
                            "empty = HakoPdu.GeometryMsgs.Vector3Array.new();"
                            "empty_bin = HakoPdu.GeometryMsgs.Vector3ArrayConverter.elixir_to_pdu_vector3_array(empty);"
                            "empty_out = HakoPdu.GeometryMsgs.Vector3ArrayConverter.pdu_to_elixir_vector3_array(empty_bin);"
                            "unless empty_out.points == [] and empty_out.weights == [] and byte_size(empty_bin) == 40, do: raise(\"bad empty varray roundtrip\")"
                        ),
                    ],
                    check=True,
                    capture_output=True,
                    text=True,
                )


if __name__ == "__main__":
    unittest.main()
