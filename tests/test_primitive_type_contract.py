import math
import shutil
import subprocess
import tempfile
import textwrap
import unittest
from pathlib import Path

from generators.generate_hako_action_msgs.action_parser import ActionParser
from generators.generate_hako_pdu_msgs.primitive_types import (
    ROS_BUILTIN_TYPES,
    SUPPORTED_BUILTIN_TYPES,
    canonical_primitive_type,
)
from generators.generate_hako_pdu_msgs.ros_message_parser import (
    get_ros_message_definition,
)
from generators.generate_hako_service_msgs.srv_parser import SrvParser
from pdu.python import binary_io
from pdu.python.std_msgs.pdu_conv_Byte import pdu_to_py_Byte, py_to_pdu_Byte
from pdu.python.std_msgs.pdu_conv_ByteMultiArray import (
    pdu_to_py_ByteMultiArray,
    py_to_pdu_ByteMultiArray,
)
from pdu.python.std_msgs.pdu_pytype_Byte import Byte
from pdu.python.std_msgs.pdu_pytype_ByteMultiArray import ByteMultiArray


ROOT = Path(__file__).resolve().parents[1]


PRIMITIVE_VALUES = {
    "bool": True,
    "byte": 255,
    "char": 254,
    "float32": 1.25,
    "float64": -2.5,
    "int8": -7,
    "uint8": 250,
    "int16": -1234,
    "uint16": 60000,
    "int32": -123456,
    "uint32": 4_000_000_000,
    "int64": -1_234_567_890_123,
    "uint64": 12_345_678_901_234,
    "string": "Hakoniwa",
}


class PrimitiveTypeContractTest(unittest.TestCase):
    def assert_value_equal(self, expected, actual):
        if isinstance(expected, float):
            self.assertTrue(math.isclose(expected, actual, rel_tol=1e-6, abs_tol=1e-6))
        else:
            self.assertEqual(expected, actual)

    def test_ros_builtin_inventory_and_canonical_aliases(self):
        self.assertEqual(len(ROS_BUILTIN_TYPES), 15)
        self.assertEqual(set(SUPPORTED_BUILTIN_TYPES), set(PRIMITIVE_VALUES))
        self.assertEqual(canonical_primitive_type("byte"), "uint8")
        self.assertEqual(canonical_primitive_type("char"), "uint8")
        self.assertEqual(canonical_primitive_type("int32"), "int32")

    def test_python_native_scalar_and_array_payload_roundtrip_for_every_supported_type(self):
        for type_name, value in PRIMITIVE_VALUES.items():
            with self.subTest(type_name=type_name, shape="scalar"):
                encoded = binary_io.typeTobin(type_name, value)
                self.assertIsNotNone(encoded)
                self.assert_value_equal(value, binary_io.binTovalue(type_name, encoded))

            with self.subTest(type_name=type_name, shape="fixed_and_variable_array"):
                values = [value, value]
                element_size = 128 if type_name == "string" else None
                encoded = binary_io.typeTobin_array(type_name, values, element_size)
                if type_name == "string":
                    decoded = binary_io.binToArrayValues(
                        type_name, encoded, len(values), element_size
                    )
                else:
                    decoded = binary_io.binToArrayValues(type_name, encoded)
                self.assertEqual(len(decoded), len(values))
                for expected, actual in zip(values, decoded):
                    self.assert_value_equal(expected, actual)

    def test_python_byte_and_byte_multi_array_generated_roundtrip(self):
        byte_value = Byte()
        byte_value.data = 255
        self.assertEqual(pdu_to_py_Byte(py_to_pdu_Byte(byte_value)).data, 255)

        array_value = ByteMultiArray()
        array_value.data = [0, 127, 255]
        restored = pdu_to_py_ByteMultiArray(py_to_pdu_ByteMultiArray(array_value))
        self.assertEqual(list(restored.data), array_value.data)

    def test_javascript_native_scalar_and_array_payload_roundtrip_for_every_supported_type(self):
        if shutil.which("node") is None:
            self.skipTest("node is not installed")
        script = textwrap.dedent(
            """
            import * as pdu from './pdu/javascript/pdu_utils.js';
            const cases = {
              bool: true, byte: 255, char: 254, float32: 1.25, float64: -2.5,
              int8: -7, uint8: 250, int16: -1234, uint16: 60000,
              int32: -123456, uint32: 4000000000,
              int64: -1234567890123n, uint64: 12345678901234n,
              string: 'Hakoniwa',
            };
            const sizes = {
              bool: 4, byte: 1, char: 1, float32: 4, float64: 8,
              int8: 1, uint8: 1, int16: 2, uint16: 2, int32: 4,
              uint32: 4, int64: 8, uint64: 8, string: 128,
            };
            for (const [typeName, value] of Object.entries(cases)) {
              const scalar = pdu.typeToBin(typeName, value, sizes[typeName]);
              const scalarValue = pdu.binToValue(typeName, scalar);
              if (scalarValue !== value) throw new Error(`${typeName} scalar mismatch`);
              const array = pdu.typesToBin(typeName, [value, value], sizes[typeName]);
              const arrayValues = pdu.binToArrayValues(typeName, array, 2, sizes[typeName]);
              if (arrayValues.length !== 2 || arrayValues.some(item => item !== value)) {
                throw new Error(`${typeName} array mismatch`);
              }
            }
            """
        )
        subprocess.run(
            ["node", "--input-type=module", "-e", script],
            cwd=ROOT,
            check=True,
        )

    def test_wstring_variants_are_rejected_by_msg_srv_and_action_parsers(self):
        variants = (
            "wstring",
            "wstring<=32",
            "wstring[]",
            "wstring[4]",
            "wstring[<=4]",
            "wstring<=32[]",
            "wstring<=32[4]",
            "wstring<=32[<=4]",
        )
        for field_type in variants:
            with self.subTest(field_type=field_type, parser="msg"):
                with tempfile.TemporaryDirectory() as tmpdir:
                    msg_dir = Path(tmpdir) / "sample_msgs" / "msg"
                    msg_dir.mkdir(parents=True)
                    (msg_dir / "Unsupported.msg").write_text(
                        f"{field_type} value\n", encoding="utf-8"
                    )
                    with self.assertRaisesRegex(ValueError, "wstring wire representation"):
                        get_ros_message_definition(
                            [tmpdir], "sample_msgs/Unsupported"
                        )

            with self.subTest(field_type=field_type, parser="srv"):
                with self.assertRaisesRegex(ValueError, "wstring wire representation"):
                    SrvParser(None)._parse_field(f"{field_type} value")

            with self.subTest(field_type=field_type, parser="action"):
                with self.assertRaisesRegex(ValueError, "wstring wire representation"):
                    ActionParser(None)._parse_field(f"{field_type} value")

if __name__ == "__main__":
    unittest.main()
