import tempfile
import struct
import sys
import unittest
from contextlib import redirect_stdout
from io import StringIO
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.dependency_resolver import DependencyResolver


class CdrGeneratorTest(unittest.TestCase):
    def _prepare_importable_output(self, output_dir: Path):
        (output_dir / "__init__.py").touch()
        python_dir = output_dir / "python"
        (python_dir / "__init__.py").touch()
        for package_dir in python_dir.iterdir():
            if package_dir.is_dir():
                (package_dir / "__init__.py").touch()

    def test_generates_cdr_converter_headers(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/SimpleStructVarray"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir)
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)

            header = output_dir / "types" / "hako_msgs" / "pdu_cpptype_cdr_conv_SimpleStructVarray.hpp"
            self.assertTrue(header.exists())

            text = header.read_text(encoding="utf-8")
            self.assertIn("hako_convert_cpp2cdr_SimpleStructVarray", text)
            self.assertIn("hako_convert_cdr2cpp_SimpleStructVarray", text)
            self.assertIn('serialize_sequence(cdr, src.varray_str)', text)
            self.assertIn('serialize_sequence_length(cdr, src.data)', text)

    def test_bool_fields_are_serialized_as_cdr_boolean(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies([
            "hako_msgs/HakoCmdHeader",
            "hako_msgs/GameControllerOperation",
        ])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir)
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)

            scalar_header = (
                output_dir / "types" / "hako_msgs" / "pdu_cpptype_cdr_conv_HakoCmdHeader.hpp"
            ).read_text(encoding="utf-8")
            self.assertIn("static_cast<bool>(src.request != 0)", scalar_header)
            self.assertIn("dst.request = value ? 1 : 0", scalar_header)

            array_header = (
                output_dir / "types" / "hako_msgs" / "pdu_cpptype_cdr_conv_GameControllerOperation.hpp"
            ).read_text(encoding="utf-8")
            self.assertIn("serialize_bool_fixed_array(cdr, src.button, 15)", array_header)
            self.assertIn("deserialize_bool_fixed_array(cdr, dst.button, 15)", array_header)

    def test_generates_python_cdr_converter_and_runtime(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/GameControllerOperation"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "pdu"
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)

            runtime = output_dir / "python" / "pdu_cdr_runtime.py"
            converter = output_dir / "python" / "hako_msgs" / "pdu_cdr_conv_GameControllerOperation.py"
            self.assertTrue(runtime.exists())
            self.assertTrue(converter.exists())

            text = converter.read_text(encoding="utf-8")
            self.assertIn("def py_to_cdr_GameControllerOperation", text)
            self.assertIn("def cdr_to_py_GameControllerOperation", text)
            self.assertIn("writer.write_float64", text)
            self.assertIn("writer.write_bool", text)

    def test_python_cdr_game_controller_operation_matches_expected_cdr_payload(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/GameControllerOperation"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "pdu"
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)
            self._prepare_importable_output(output_dir)

            sys.path.insert(0, str(Path(tmpdir)))
            loaded = [name for name in sys.modules if name == "pdu" or name.startswith("pdu.")]
            for name in loaded:
                del sys.modules[name]
            try:
                from pdu.python.hako_msgs.pdu_cdr_conv_GameControllerOperation import (
                    cdr_to_py_GameControllerOperation,
                    py_to_cdr_GameControllerOperation,
                )
                from pdu.python.hako_msgs.pdu_pytype_GameControllerOperation import (
                    GameControllerOperation,
                )

                obj = GameControllerOperation()
                obj.axis = [0.5, -1.0, 2.0, -3.0, 4.0, -5.0]
                obj.button = [
                    True, False, True, True, False,
                    True, False, True, True, False,
                    True, False, True, True, False,
                ]

                payload = py_to_cdr_GameControllerOperation(obj)
                expected = (
                    b"\x00\x01\x00\x00"
                    + struct.pack("<6d", *obj.axis)
                    + struct.pack("<15?", *obj.button)
                )
                self.assertEqual(payload, expected)

                restored = cdr_to_py_GameControllerOperation(payload)
                self.assertEqual(restored.axis, obj.axis)
                self.assertEqual(restored.button, obj.button)
            finally:
                sys.path.remove(str(Path(tmpdir)))
                for name in [name for name in sys.modules if name == "pdu" or name.startswith("pdu.")]:
                    del sys.modules[name]


if __name__ == "__main__":
    unittest.main()
