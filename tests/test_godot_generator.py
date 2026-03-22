import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.offset_parser import parse_offset_file


class GodotGeneratorTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        cls.template_dir = cls.repo_root / "template"

    def make_message_def(self, package, message, fields):
        return {
            "package": package,
            "message": message,
            "fields": fields,
        }

    def test_generate_all_emits_godot_runtime_and_gd_types(self):
        generator = CodeGenerator(self.template_dir)
        message_cache = {
            "hako_msgs/GameControllerOperation": self.make_message_def(
                "hako_msgs",
                "GameControllerOperation",
                [
                    {"name": "axis", "type": "float64[6]"},
                    {"name": "button", "type": "bool[15]"},
                ],
            )
        }

        with tempfile.TemporaryDirectory() as tmpdir:
            output_root = Path(tmpdir)
            generator.generate_all(message_cache, {}, output_root)

            runtime_path = output_root / "godot_cpp_runtime" / "PduRuntime.hpp"
            type_path = output_root / "godot_gd" / "hako_msgs" / "GameControllerOperation.gd"

            self.assertTrue(runtime_path.exists())
            self.assertTrue(type_path.exists())

            runtime_text = runtime_path.read_text()
            type_text = type_path.read_text()

            self.assertIn("namespace hako::godot_runtime", runtime_text)
            self.assertIn("struct PduMetaData", runtime_text)
            self.assertIn("class DynamicAllocator", runtime_text)
            self.assertIn("inline godot::PackedByteArray build_pdu", runtime_text)

            self.assertIn("class_name HakoPdu_hako_msgs_GameControllerOperation", type_text)
            self.assertIn("extends RefCounted", type_text)
            self.assertIn("var axis: PackedFloat64Array = PackedFloat64Array()", type_text)
            self.assertIn("var button: Array = []", type_text)
            self.assertIn("static func from_dict(d: Dictionary)", type_text)
            self.assertIn("func to_dict() -> Dictionary:", type_text)

    def test_generate_converter_emits_primitive_varray_and_nested_struct_varray_patterns(self):
        generator = CodeGenerator(self.template_dir)

        disturbance_user_custom_def = self.make_message_def(
            "hako_msgs",
            "DisturbanceUserCustom",
            [
                {"name": "data", "type": "float64[]"},
            ],
        )
        disturbance_def = self.make_message_def(
            "hako_msgs",
            "Disturbance",
            [
                {"name": "d_temp", "type": "hako_msgs/DisturbanceTemperature"},
                {"name": "d_wind", "type": "hako_msgs/DisturbanceWind"},
                {"name": "d_atm", "type": "hako_msgs/DisturbanceAtm"},
                {"name": "d_boundary", "type": "hako_msgs/DisturbanceBoundary"},
                {"name": "d_user_custom", "type": "hako_msgs/DisturbanceUserCustom[]"},
            ],
        )

        disturbance_user_custom_offsets = parse_offset_file(
            self.repo_root / "pdu" / "offset" / "hako_msgs" / "DisturbanceUserCustom.offset"
        )
        disturbance_offsets = parse_offset_file(
            self.repo_root / "pdu" / "offset" / "hako_msgs" / "Disturbance.offset"
        )

        with tempfile.TemporaryDirectory() as tmpdir:
            output_root = Path(tmpdir)
            generator.generate_godot_cpp_converter(
                disturbance_user_custom_def, disturbance_user_custom_offsets, output_root
            )
            generator.generate_godot_cpp_converter(disturbance_def, disturbance_offsets, output_root)

            primitive_conv_path = output_root / "godot_cpp" / "hako_msgs" / "pdu_conv_DisturbanceUserCustom.hpp"
            nested_conv_path = output_root / "godot_cpp" / "hako_msgs" / "pdu_conv_Disturbance.hpp"

            self.assertTrue(primitive_conv_path.exists())
            self.assertTrue(nested_conv_path.exists())

            primitive_conv_text = primitive_conv_path.read_text()
            nested_conv_text = nested_conv_path.read_text()

            self.assertIn("inline godot::Dictionary pdu_to_godot_DisturbanceUserCustom", primitive_conv_text)
            self.assertIn('obj["data"] = values;', primitive_conv_text)
            self.assertIn("godot::PackedFloat64Array values;", primitive_conv_text)
            self.assertIn('if (obj.has("data")) {', primitive_conv_text)
            self.assertIn("variant_to_packed_float64_array", primitive_conv_text)
            self.assertIn("get_binary_for_float64(values[i])", primitive_conv_text)

            self.assertIn("binary_read_recursive_DisturbanceUserCustom", nested_conv_text)
            self.assertIn('obj["d_user_custom"] = values;', nested_conv_text)
            self.assertIn("writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 8), offset_from_heap);", nested_conv_text)
            self.assertIn("binary_write_recursive_DisturbanceUserCustom(", nested_conv_text)

    def test_generate_converter_emits_string_varray_and_struct_array_patterns(self):
        generator = CodeGenerator(self.template_dir)

        joint_state_def = self.make_message_def(
            "sensor_msgs",
            "JointState",
            [
                {"name": "header", "type": "std_msgs/Header"},
                {"name": "name", "type": "string[]"},
                {"name": "position", "type": "float64[]"},
                {"name": "velocity", "type": "float64[]"},
                {"name": "effort", "type": "float64[]"},
            ],
        )
        simple_struct_varray_def = self.make_message_def(
            "hako_msgs",
            "SimpleStructVarray",
            [
                {"name": "aaa", "type": "int32"},
                {"name": "fixed_str", "type": "string[2]"},
                {"name": "varray_str", "type": "string[]"},
                {"name": "fixed_array", "type": "SimpleVarray[5]"},
                {"name": "data", "type": "SimpleVarray[]"},
            ],
        )

        joint_state_offsets = parse_offset_file(
            self.repo_root / "pdu" / "offset" / "sensor_msgs" / "JointState.offset"
        )
        simple_struct_varray_offsets = parse_offset_file(
            self.repo_root / "pdu" / "offset" / "hako_msgs" / "SimpleStructVarray.offset"
        )

        with tempfile.TemporaryDirectory() as tmpdir:
            output_root = Path(tmpdir)
            generator.generate_godot_cpp_converter(joint_state_def, joint_state_offsets, output_root)
            generator.generate_godot_cpp_converter(
                simple_struct_varray_def, simple_struct_varray_offsets, output_root
            )

            joint_state_conv_path = output_root / "godot_cpp" / "sensor_msgs" / "pdu_conv_JointState.hpp"
            simple_struct_varray_conv_path = output_root / "godot_cpp" / "hako_msgs" / "pdu_conv_SimpleStructVarray.hpp"

            self.assertTrue(joint_state_conv_path.exists())
            self.assertTrue(simple_struct_varray_conv_path.exists())

            joint_state_conv_text = joint_state_conv_path.read_text()
            simple_struct_varray_conv_text = simple_struct_varray_conv_path.read_text()

            self.assertIn("read_string(", joint_state_conv_text)
            self.assertIn('obj["name"] = values;', joint_state_conv_text)
            self.assertIn("get_binary_for_string(hako::godot_runtime::variant_to_string(values[i]), 128)", joint_state_conv_text)

            self.assertIn('obj["fixed_str"] = values;', simple_struct_varray_conv_text)
            self.assertIn('obj["varray_str"] = values;', simple_struct_varray_conv_text)
            self.assertIn('obj["fixed_array"] = values;', simple_struct_varray_conv_text)
            self.assertIn('obj["data"] = values;', simple_struct_varray_conv_text)
            self.assertIn("binary_read_recursive_SimpleVarray(", simple_struct_varray_conv_text)
            self.assertIn("writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 24), offset_from_heap);", simple_struct_varray_conv_text)


if __name__ == "__main__":
    unittest.main()
