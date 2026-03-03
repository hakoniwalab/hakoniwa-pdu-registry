import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.offset_parser import parse_offset_file


class CSharpV2GeneratorTest(unittest.TestCase):
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

    def test_generate_all_emits_runtime_and_type_definition(self):
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

            runtime_path = output_root / "csharp_v2" / "PduRuntime.cs"
            type_path = output_root / "csharp_v2" / "hako_msgs" / "pdu_type_GameControllerOperation.cs"

            self.assertTrue(runtime_path.exists())
            self.assertTrue(type_path.exists())

            runtime_text = runtime_path.read_text()
            type_text = type_path.read_text()

            self.assertIn("namespace Hakoniwa.Pdu.CSharpV2", runtime_text)
            self.assertIn("public sealed class PduMetaData", runtime_text)
            self.assertIn("public sealed class DynamicAllocator", runtime_text)

            self.assertIn("namespace Hakoniwa.Pdu.CSharpV2.hako_msgs", type_text)
            self.assertIn("public class GameControllerOperation", type_text)
            self.assertIn("public List<double> axis { get; set; } = new List<double>()", type_text)
            self.assertIn("public List<bool> button { get; set; } = new List<bool>()", type_text)

    def test_generate_converter_emits_fixed_array_and_struct_varray_patterns(self):
        generator = CodeGenerator(self.template_dir)

        game_controller_def = self.make_message_def(
            "hako_msgs",
            "GameControllerOperation",
            [
                {"name": "axis", "type": "float64[6]"},
                {"name": "button", "type": "bool[15]"},
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

        game_offsets = parse_offset_file(self.repo_root / "pdu" / "offset" / "hako_msgs" / "GameControllerOperation.offset")
        disturbance_offsets = parse_offset_file(self.repo_root / "pdu" / "offset" / "hako_msgs" / "Disturbance.offset")

        with tempfile.TemporaryDirectory() as tmpdir:
            output_root = Path(tmpdir)
            generator.generate_csharp_v2_converter(game_controller_def, game_offsets, output_root)
            generator.generate_csharp_v2_converter(disturbance_def, disturbance_offsets, output_root)

            game_conv_path = output_root / "csharp_v2" / "hako_msgs" / "pdu_conv_GameControllerOperation.cs"
            disturbance_conv_path = output_root / "csharp_v2" / "hako_msgs" / "pdu_conv_Disturbance.cs"

            self.assertTrue(game_conv_path.exists())
            self.assertTrue(disturbance_conv_path.exists())

            game_conv_text = game_conv_path.read_text()
            disturbance_conv_text = disturbance_conv_path.read_text()

            self.assertIn("public static class GameControllerOperationConverter", game_conv_text)
            self.assertIn("obj.axis = new List<double>()", game_conv_text)
            self.assertIn("obj.button = new List<bool>()", game_conv_text)
            self.assertIn("for (var i = 0; i < obj.axis.Count; i++)", game_conv_text)
            self.assertIn("PduRuntime.GetBinaryForFloat64(obj.axis[i])", game_conv_text)
            self.assertIn("PduRuntime.GetBinaryForBool(obj.button[i])", game_conv_text)

            self.assertIn("public static class DisturbanceConverter", disturbance_conv_text)
            self.assertIn("obj.d_user_custom = new List<DisturbanceUserCustom>()", disturbance_conv_text)
            self.assertIn("var arraySize = obj.d_user_custom.Count;", disturbance_conv_text)
            self.assertIn("writer.HeapAllocator.Add(new byte[arraySize * 8], offsetFromHeap);", disturbance_conv_text)
            self.assertIn("DisturbanceUserCustomConverter.BinaryWriteRecursive(offsetFromHeap + (i * 8), writer, writer.HeapAllocator, obj.d_user_custom[i]);", disturbance_conv_text)

    def test_generate_converter_emits_string_varray_and_fixed_string_patterns(self):
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

        joint_state_offsets = parse_offset_file(self.repo_root / "pdu" / "offset" / "sensor_msgs" / "JointState.offset")
        simple_struct_varray_offsets = parse_offset_file(self.repo_root / "pdu" / "offset" / "hako_msgs" / "SimpleStructVarray.offset")

        with tempfile.TemporaryDirectory() as tmpdir:
            output_root = Path(tmpdir)
            generator.generate_csharp_v2_converter(joint_state_def, joint_state_offsets, output_root)
            generator.generate_csharp_v2_converter(simple_struct_varray_def, simple_struct_varray_offsets, output_root)

            joint_state_conv_path = output_root / "csharp_v2" / "sensor_msgs" / "pdu_conv_JointState.cs"
            simple_struct_varray_conv_path = output_root / "csharp_v2" / "hako_msgs" / "pdu_conv_SimpleStructVarray.cs"

            self.assertTrue(joint_state_conv_path.exists())
            self.assertTrue(simple_struct_varray_conv_path.exists())

            joint_state_conv_text = joint_state_conv_path.read_text()
            simple_struct_varray_conv_text = simple_struct_varray_conv_path.read_text()

            self.assertIn("obj.name = new List<string>()", joint_state_conv_text)
            self.assertIn("obj.name.Add(PduRuntime.ReadString(binaryData, meta.HeapOff + offsetFromHeap + (i * 128), 128));", joint_state_conv_text)
            self.assertIn("writer.HeapAllocator.Add(PduRuntime.GetBinaryForString(obj.name[i], 128));", joint_state_conv_text)

            self.assertIn("obj.fixed_str = new List<string>()", simple_struct_varray_conv_text)
            self.assertIn("obj.fixed_str.Add(PduRuntime.ReadString(binaryData, baseOff + 4 + (i * 128), 128));", simple_struct_varray_conv_text)
            self.assertIn("obj.varray_str = new List<string>()", simple_struct_varray_conv_text)
            self.assertIn("writer.HeapAllocator.Add(PduRuntime.GetBinaryForString(obj.varray_str[i], 128));", simple_struct_varray_conv_text)
            self.assertIn("obj.data = new List<SimpleVarray>()", simple_struct_varray_conv_text)
            self.assertIn("writer.HeapAllocator.Add(new byte[arraySize * 24], offsetFromHeap);", simple_struct_varray_conv_text)
            self.assertIn("SimpleVarrayConverter.BinaryWriteRecursive(offsetFromHeap + (i * 24), writer, writer.HeapAllocator, obj.data[i]);", simple_struct_varray_conv_text)


if __name__ == "__main__":
    unittest.main()
