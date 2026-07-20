import json
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.validate_generated_artifacts import ensure_cpp_oracle_tools


class RubyElixirGeneratedArtifactsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        cls.has_ruby = shutil.which("ruby") is not None
        cls.has_elixir = shutil.which("elixir") is not None and shutil.which("elixirc") is not None
        cls.tools = ensure_cpp_oracle_tools(cls.repo_root)

        if str(cls.repo_root) not in sys.path:
            sys.path.insert(0, str(cls.repo_root))

        cls._beam_tmp = None
        if cls.has_elixir:
            cls._beam_tmp = tempfile.TemporaryDirectory()
            cls.beam_dir = Path(cls._beam_tmp.name)
            subprocess.run(
                [
                    "elixirc",
                    "-o",
                    str(cls.beam_dir),
                    "pdu/elixir/builtin_interfaces/pdu_type_Time.ex",
                    "pdu/elixir/builtin_interfaces/pdu_conv_Time.ex",
                    "pdu/elixir/std_msgs/pdu_type_Header.ex",
                    "pdu/elixir/std_msgs/pdu_conv_Header.ex",
                    "pdu/elixir/geometry_msgs/pdu_type_Point.ex",
                    "pdu/elixir/geometry_msgs/pdu_conv_Point.ex",
                    "pdu/elixir/geometry_msgs/pdu_type_Vector3.ex",
                    "pdu/elixir/geometry_msgs/pdu_conv_Vector3.ex",
                    "pdu/elixir/hako_msgs/pdu_type_GameControllerOperation.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_GameControllerOperation.ex",
                    "pdu/elixir/hako_msgs/pdu_type_DisturbanceUserCustom.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_DisturbanceUserCustom.ex",
                    "pdu/elixir/hako_msgs/pdu_type_DisturbanceTemperature.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_DisturbanceTemperature.ex",
                    "pdu/elixir/hako_msgs/pdu_type_DisturbanceWind.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_DisturbanceWind.ex",
                    "pdu/elixir/hako_msgs/pdu_type_DisturbanceAtm.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_DisturbanceAtm.ex",
                    "pdu/elixir/hako_msgs/pdu_type_DisturbanceBoundary.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_DisturbanceBoundary.ex",
                    "pdu/elixir/hako_msgs/pdu_type_Disturbance.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_Disturbance.ex",
                    "pdu/elixir/hako_msgs/pdu_type_SimpleVarray.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_SimpleVarray.ex",
                    "pdu/elixir/hako_msgs/pdu_type_SimpleStructVarray.ex",
                    "pdu/elixir/hako_msgs/pdu_conv_SimpleStructVarray.ex",
                    "pdu/elixir/sensor_msgs/pdu_type_JointState.ex",
                    "pdu/elixir/sensor_msgs/pdu_conv_JointState.ex",
                ],
                cwd=cls.repo_root,
                check=True,
                capture_output=True,
                text=True,
            )

    @classmethod
    def tearDownClass(cls):
        if cls._beam_tmp is not None:
            cls._beam_tmp.cleanup()

    def run_ruby_json(self, script, *args):
        if not self.has_ruby:
            self.skipTest("ruby is not available")
        result = subprocess.run(
            ["ruby", "-I./pdu/ruby", "-e", script, *map(str, args)],
            cwd=self.repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        return json.loads(result.stdout)

    def run_ruby(self, script, *args):
        if not self.has_ruby:
            self.skipTest("ruby is not available")
        subprocess.run(
            ["ruby", "-I./pdu/ruby", "-e", script, *map(str, args)],
            cwd=self.repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

    def run_elixir_json(self, script, *args):
        if not self.has_elixir:
            self.skipTest("elixir is not available")
        result = subprocess.run(
            ["elixir", "-pa", str(self.beam_dir), "-e", self.elixir_json_prelude() + script, *map(str, args)],
            cwd=self.repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        return json.loads(result.stdout)

    def run_elixir(self, script, *args):
        if not self.has_elixir:
            self.skipTest("elixir is not available")
        subprocess.run(
            ["elixir", "-pa", str(self.beam_dir), "-e", script, *map(str, args)],
            cwd=self.repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

    @staticmethod
    def elixir_json_prelude():
        return r'''
defmodule TestJson do
  def encode(value) when is_map(value) do
    "{" <> (value |> Enum.map(fn {k, v} -> encode(to_string(k)) <> ":" <> encode(v) end) |> Enum.join(",")) <> "}"
  end
  def encode(value) when is_list(value), do: "[" <> Enum.map_join(value, ",", &encode/1) <> "]"
  def encode(value) when is_binary(value), do: inspect(value)
  def encode(value) when is_boolean(value), do: if(value, do: "true", else: "false")
  def encode(value) when is_integer(value), do: Integer.to_string(value)
  def encode(value) when is_float(value), do: Float.to_string(value)
  def encode(nil), do: "null"
end
'''

    def make_cpp_bin(self, tool_name, filename):
        path = Path(tempfile.mkdtemp()) / filename
        subprocess.run(
            [str(self.tools[tool_name]), str(path)],
            cwd=self.repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        return path

    def assert_language_generated_matches_python(self, lang_bin, decoder, expected):
        restored = decoder(bytearray(Path(lang_bin).read_bytes()))
        self.assertEqual(self.normalize(restored), expected)

    def normalize(self, obj):
        if obj.__class__.__name__ == "GameControllerOperation":
            return {"axis": list(obj.axis), "button": [bool(v) for v in obj.button]}
        if obj.__class__.__name__ == "DisturbanceUserCustom":
            return {"data": self.decode_f64_list(obj.data)}
        if obj.__class__.__name__ == "JointState":
            return {
                "frame_id": obj.header.frame_id,
                "name": self.decode_string_list(obj.name),
                "position": self.decode_f64_list(obj.position),
                "velocity": self.decode_f64_list(obj.velocity),
                "effort": self.decode_f64_list(obj.effort),
            }
        if obj.__class__.__name__ == "SimpleStructVarray":
            return {
                "aaa": obj.aaa,
                "fixed_str": list(obj.fixed_str),
                "varray_str": self.decode_string_list(obj.varray_str),
                "fixed_array": [self.normalize_simple_varray(item) for item in obj.fixed_array],
                "data": [self.normalize_simple_varray(item) for item in obj.data],
            }
        if obj.__class__.__name__ == "Disturbance":
            return {"d_user_custom": [self.decode_f64_list(item.data) for item in obj.d_user_custom]}
        raise TypeError(f"Unsupported object: {obj.__class__.__name__}")

    @staticmethod
    def normalize_simple_varray(item):
        data = list(item.data) if isinstance(item.data, list) else list(bytes(item.data))
        fixed = list(item.fixed_array) if isinstance(item.fixed_array, list) else list(bytes(item.fixed_array))
        return {"data": data, "fixed_array": fixed, "p_mem1": item.p_mem1}

    @staticmethod
    def decode_f64_list(value):
        if isinstance(value, list):
            return value
        if len(value) > 0 and isinstance(value[0], float):
            return list(value)
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value))) if len(value) > 0 else []

    @staticmethod
    def decode_string_list(value):
        if isinstance(value, list):
            return value
        raw = bytes(value)
        return [raw[index:index + 128].split(b"\0", 1)[0].decode("utf-8") for index in range(0, len(raw), 128)]

    def test_game_controller_operation_cpp_oracle_ruby_elixir_interop(self):
        expected = {
            "axis": [0.5, -1.0, 2.0, -3.0, 4.0, -5.0],
            "button": [True, False, True, True, False, True, False, True, True, False, True, False, True, True, False],
        }
        cpp_bin = self.make_cpp_bin("game_controller_operation_dump", "game_controller_operation_cpp.bin")

        ruby_decode = r'''
require 'json'
require 'hako_msgs/pdu_conv_GameControllerOperation'
obj = HakoPdu::HakoMsgs::GameControllerOperationConverter.pdu_to_ruby_game_controller_operation(File.binread(ARGV[0]))
puts JSON.generate({ axis: obj.axis, button: obj.button })
'''
        self.assertEqual(self.run_ruby_json(ruby_decode, cpp_bin), expected)

        elixir_decode = r'''
bin = File.read!(List.first(System.argv()))
obj = HakoPdu.HakoMsgs.GameControllerOperationConverter.pdu_to_elixir_game_controller_operation(bin)
IO.puts(TestJson.encode(%{axis: obj.axis, button: obj.button}))
'''
        self.assertEqual(self.run_elixir_json(elixir_decode, cpp_bin), expected)

        from pdu.python.hako_msgs.pdu_conv_GameControllerOperation import pdu_to_py_GameControllerOperation

        with tempfile.TemporaryDirectory() as tmp:
            ruby_bin = Path(tmp) / "ruby.bin"
            elixir_bin = Path(tmp) / "elixir.bin"
            ruby_encode = r'''
require 'hako_msgs/pdu_conv_GameControllerOperation'
obj = HakoPdu::HakoMsgs::GameControllerOperation.new
obj.axis = [0.5, -1.0, 2.0, -3.0, 4.0, -5.0]
obj.button = [true, false, true, true, false, true, false, true, true, false, true, false, true, true, false]
File.binwrite(ARGV[0], HakoPdu::HakoMsgs::GameControllerOperationConverter.ruby_to_pdu_game_controller_operation(obj))
'''
            self.run_ruby(ruby_encode, ruby_bin)
            self.assert_language_generated_matches_python(ruby_bin, pdu_to_py_GameControllerOperation, expected)

            elixir_encode = r'''
obj = HakoPdu.HakoMsgs.GameControllerOperation.new(%{
  axis: [0.5, -1.0, 2.0, -3.0, 4.0, -5.0],
  button: [true, false, true, true, false, true, false, true, true, false, true, false, true, true, false]
})
File.write!(List.first(System.argv()), HakoPdu.HakoMsgs.GameControllerOperationConverter.elixir_to_pdu_game_controller_operation(obj))
'''
            self.run_elixir(elixir_encode, elixir_bin)
            self.assert_language_generated_matches_python(elixir_bin, pdu_to_py_GameControllerOperation, expected)

    def test_disturbance_user_custom_cpp_oracle_ruby_elixir_interop(self):
        expected = {"data": [1.25, 2.5]}
        cpp_bin = self.make_cpp_bin("disturbance_user_custom_dump", "disturbance_user_custom_cpp.bin")

        ruby_decode = r'''
require 'json'
require 'hako_msgs/pdu_conv_DisturbanceUserCustom'
obj = HakoPdu::HakoMsgs::DisturbanceUserCustomConverter.pdu_to_ruby_disturbance_user_custom(File.binread(ARGV[0]))
puts JSON.generate({ data: obj.data })
'''
        self.assertEqual(self.run_ruby_json(ruby_decode, cpp_bin), expected)

        elixir_decode = r'''
bin = File.read!(List.first(System.argv()))
obj = HakoPdu.HakoMsgs.DisturbanceUserCustomConverter.pdu_to_elixir_disturbance_user_custom(bin)
IO.puts(TestJson.encode(%{data: obj.data}))
'''
        self.assertEqual(self.run_elixir_json(elixir_decode, cpp_bin), expected)

        from pdu.python.hako_msgs.pdu_conv_DisturbanceUserCustom import pdu_to_py_DisturbanceUserCustom

        with tempfile.TemporaryDirectory() as tmp:
            ruby_bin = Path(tmp) / "ruby.bin"
            elixir_bin = Path(tmp) / "elixir.bin"
            ruby_encode = r'''
require 'hako_msgs/pdu_conv_DisturbanceUserCustom'
obj = HakoPdu::HakoMsgs::DisturbanceUserCustom.new
obj.data = [1.25, 2.5]
File.binwrite(ARGV[0], HakoPdu::HakoMsgs::DisturbanceUserCustomConverter.ruby_to_pdu_disturbance_user_custom(obj))
'''
            self.run_ruby(ruby_encode, ruby_bin)
            self.assert_language_generated_matches_python(ruby_bin, pdu_to_py_DisturbanceUserCustom, expected)

            elixir_encode = r'''
obj = HakoPdu.HakoMsgs.DisturbanceUserCustom.new(%{data: [1.25, 2.5]})
File.write!(List.first(System.argv()), HakoPdu.HakoMsgs.DisturbanceUserCustomConverter.elixir_to_pdu_disturbance_user_custom(obj))
'''
            self.run_elixir(elixir_encode, elixir_bin)
            self.assert_language_generated_matches_python(elixir_bin, pdu_to_py_DisturbanceUserCustom, expected)

    def test_joint_state_cpp_oracle_ruby_elixir_interop(self):
        expected = {
            "frame_id": "frame",
            "name": ["a", "b"],
            "position": [1.0, 2.0],
            "velocity": [3.0],
            "effort": [4.0],
        }
        cpp_bin = self.make_cpp_bin("joint_state_dump", "joint_state_cpp.bin")

        ruby_decode = r'''
require 'json'
require 'sensor_msgs/pdu_conv_JointState'
obj = HakoPdu::SensorMsgs::JointStateConverter.pdu_to_ruby_joint_state(File.binread(ARGV[0]))
puts JSON.generate({ frame_id: obj.header.frame_id, name: obj.name, position: obj.position, velocity: obj.velocity, effort: obj.effort })
'''
        self.assertEqual(self.run_ruby_json(ruby_decode, cpp_bin), expected)

        elixir_decode = r'''
bin = File.read!(List.first(System.argv()))
obj = HakoPdu.SensorMsgs.JointStateConverter.pdu_to_elixir_joint_state(bin)
IO.puts(TestJson.encode(%{frame_id: obj.header.frame_id, name: obj.name, position: obj.position, velocity: obj.velocity, effort: obj.effort}))
'''
        self.assertEqual(self.run_elixir_json(elixir_decode, cpp_bin), expected)

        from pdu.python.builtin_interfaces.pdu_pytype_Time import Time
        from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState
        from pdu.python.std_msgs.pdu_pytype_Header import Header

        with tempfile.TemporaryDirectory() as tmp:
            ruby_bin = Path(tmp) / "ruby.bin"
            elixir_bin = Path(tmp) / "elixir.bin"
            ruby_encode = r'''
require 'sensor_msgs/pdu_conv_JointState'
obj = HakoPdu::SensorMsgs::JointState.new
obj.header = HakoPdu::StdMsgs::Header.new
obj.header.stamp = HakoPdu::BuiltinInterfaces::Time.new
obj.header.frame_id = 'frame'
obj.name = ['a', 'b']
obj.position = [1.0, 2.0]
obj.velocity = [3.0]
obj.effort = [4.0]
File.binwrite(ARGV[0], HakoPdu::SensorMsgs::JointStateConverter.ruby_to_pdu_joint_state(obj))
'''
            self.run_ruby(ruby_encode, ruby_bin)
            self.assert_language_generated_matches_python(ruby_bin, pdu_to_py_JointState, expected)

            elixir_encode = r'''
header = HakoPdu.StdMsgs.Header.new(%{stamp: HakoPdu.BuiltinInterfaces.Time.new(), frame_id: "frame"})
obj = HakoPdu.SensorMsgs.JointState.new(%{header: header, name: ["a", "b"], position: [1.0, 2.0], velocity: [3.0], effort: [4.0]})
File.write!(List.first(System.argv()), HakoPdu.SensorMsgs.JointStateConverter.elixir_to_pdu_joint_state(obj))
'''
            self.run_elixir(elixir_encode, elixir_bin)
            self.assert_language_generated_matches_python(elixir_bin, pdu_to_py_JointState, expected)

    def test_simple_struct_varray_cpp_oracle_ruby_elixir_interop(self):
        expected = {
            "aaa": 7,
            "fixed_str": ["alpha", "beta"],
            "varray_str": ["gamma", "delta"],
            "fixed_array": [
                {"data": [1, 2], "fixed_array": [3, 4] + [0] * 8, "p_mem1": 5},
                {"data": [6], "fixed_array": [7, 8] + [0] * 8, "p_mem1": 9},
                {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
                {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
                {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
            ],
            "data": [
                {"data": [10, 11], "fixed_array": [12, 13] + [0] * 8, "p_mem1": 14},
                {"data": [15], "fixed_array": [16, 17] + [0] * 8, "p_mem1": 18},
            ],
        }
        cpp_bin = self.make_cpp_bin("simple_struct_varray_dump", "simple_struct_varray_cpp.bin")

        ruby_decode = r'''
require 'json'
require 'hako_msgs/pdu_conv_SimpleStructVarray'
def sv(item)
  { data: item.data, fixed_array: item.fixed_array, p_mem1: item.p_mem1 }
end
obj = HakoPdu::HakoMsgs::SimpleStructVarrayConverter.pdu_to_ruby_simple_struct_varray(File.binread(ARGV[0]))
puts JSON.generate({ aaa: obj.aaa, fixed_str: obj.fixed_str, varray_str: obj.varray_str, fixed_array: obj.fixed_array.map { |item| sv(item) }, data: obj.data.map { |item| sv(item) } })
'''
        self.assertEqual(self.run_ruby_json(ruby_decode, cpp_bin), expected)

        elixir_decode = r'''
bin = File.read!(List.first(System.argv()))
obj = HakoPdu.HakoMsgs.SimpleStructVarrayConverter.pdu_to_elixir_simple_struct_varray(bin)
sv = fn item -> %{data: item.data, fixed_array: item.fixed_array, p_mem1: item.p_mem1} end
IO.puts(TestJson.encode(%{aaa: obj.aaa, fixed_str: obj.fixed_str, varray_str: obj.varray_str, fixed_array: Enum.map(obj.fixed_array, sv), data: Enum.map(obj.data, sv)}))
'''
        self.assertEqual(self.run_elixir_json(elixir_decode, cpp_bin), expected)

        from pdu.python.hako_msgs.pdu_conv_SimpleStructVarray import pdu_to_py_SimpleStructVarray

        with tempfile.TemporaryDirectory() as tmp:
            ruby_bin = Path(tmp) / "ruby.bin"
            elixir_bin = Path(tmp) / "elixir.bin"
            ruby_encode = r'''
require 'hako_msgs/pdu_conv_SimpleStructVarray'
def make_sv(data, fixed, p_mem1)
  HakoPdu::HakoMsgs::SimpleVarray.new(data: data, fixed_array: fixed + ([0] * (10 - fixed.length)), p_mem1: p_mem1)
end
obj = HakoPdu::HakoMsgs::SimpleStructVarray.new
obj.aaa = 7
obj.fixed_str = ['alpha', 'beta']
obj.varray_str = ['gamma', 'delta']
obj.fixed_array = [
  make_sv([1, 2], [3, 4], 5),
  make_sv([6], [7, 8], 9),
  make_sv([], [], 0),
  make_sv([], [], 0),
  make_sv([], [], 0)
]
obj.data = [
  make_sv([10, 11], [12, 13], 14),
  make_sv([15], [16, 17], 18)
]
File.binwrite(ARGV[0], HakoPdu::HakoMsgs::SimpleStructVarrayConverter.ruby_to_pdu_simple_struct_varray(obj))
'''
            self.run_ruby(ruby_encode, ruby_bin)
            self.assert_language_generated_matches_python(ruby_bin, pdu_to_py_SimpleStructVarray, expected)

            elixir_encode = r'''
make_sv = fn data, fixed, p_mem1 ->
  HakoPdu.HakoMsgs.SimpleVarray.new(%{data: data, fixed_array: fixed ++ List.duplicate(0, 10 - length(fixed)), p_mem1: p_mem1})
end
obj = HakoPdu.HakoMsgs.SimpleStructVarray.new(%{
  aaa: 7,
  fixed_str: ["alpha", "beta"],
  varray_str: ["gamma", "delta"],
  fixed_array: [
    make_sv.([1, 2], [3, 4], 5),
    make_sv.([6], [7, 8], 9),
    make_sv.([], [], 0),
    make_sv.([], [], 0),
    make_sv.([], [], 0)
  ],
  data: [
    make_sv.([10, 11], [12, 13], 14),
    make_sv.([15], [16, 17], 18)
  ]
})
File.write!(List.first(System.argv()), HakoPdu.HakoMsgs.SimpleStructVarrayConverter.elixir_to_pdu_simple_struct_varray(obj))
'''
            self.run_elixir(elixir_encode, elixir_bin)
            self.assert_language_generated_matches_python(elixir_bin, pdu_to_py_SimpleStructVarray, expected)

    def test_disturbance_cpp_oracle_ruby_elixir_interop(self):
        expected = {"d_user_custom": [[1.25, 2.5], [3.75]]}
        cpp_bin = self.make_cpp_bin("disturbance_dump", "disturbance_cpp.bin")

        ruby_decode = r'''
require 'json'
require 'hako_msgs/pdu_conv_Disturbance'
obj = HakoPdu::HakoMsgs::DisturbanceConverter.pdu_to_ruby_disturbance(File.binread(ARGV[0]))
puts JSON.generate({ d_user_custom: obj.d_user_custom.map { |item| item.data } })
'''
        self.assertEqual(self.run_ruby_json(ruby_decode, cpp_bin), expected)

        elixir_decode = r'''
bin = File.read!(List.first(System.argv()))
obj = HakoPdu.HakoMsgs.DisturbanceConverter.pdu_to_elixir_disturbance(bin)
IO.puts(TestJson.encode(%{d_user_custom: Enum.map(obj.d_user_custom, fn item -> item.data end)}))
'''
        self.assertEqual(self.run_elixir_json(elixir_decode, cpp_bin), expected)

        from pdu.python.hako_msgs.pdu_conv_Disturbance import pdu_to_py_Disturbance

        with tempfile.TemporaryDirectory() as tmp:
            ruby_bin = Path(tmp) / "ruby.bin"
            elixir_bin = Path(tmp) / "elixir.bin"
            ruby_encode = r'''
require 'hako_msgs/pdu_conv_Disturbance'
item1 = HakoPdu::HakoMsgs::DisturbanceUserCustom.new(data: [1.25, 2.5])
item2 = HakoPdu::HakoMsgs::DisturbanceUserCustom.new(data: [3.75])
obj = HakoPdu::HakoMsgs::Disturbance.new
obj.d_user_custom = [item1, item2]
File.binwrite(ARGV[0], HakoPdu::HakoMsgs::DisturbanceConverter.ruby_to_pdu_disturbance(obj))
'''
            self.run_ruby(ruby_encode, ruby_bin)
            self.assert_language_generated_matches_python(ruby_bin, pdu_to_py_Disturbance, expected)

            elixir_encode = r'''
item1 = HakoPdu.HakoMsgs.DisturbanceUserCustom.new(%{data: [1.25, 2.5]})
item2 = HakoPdu.HakoMsgs.DisturbanceUserCustom.new(%{data: [3.75]})
obj = HakoPdu.HakoMsgs.Disturbance.new(%{d_user_custom: [item1, item2]})
File.write!(List.first(System.argv()), HakoPdu.HakoMsgs.DisturbanceConverter.elixir_to_pdu_disturbance(obj))
'''
            self.run_elixir(elixir_encode, elixir_bin)
            self.assert_language_generated_matches_python(elixir_bin, pdu_to_py_Disturbance, expected)


if __name__ == "__main__":
    unittest.main()
