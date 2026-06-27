import tempfile
import unittest
from contextlib import redirect_stdout
from io import StringIO
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.dependency_resolver import DependencyResolver


class CdrGeneratorTest(unittest.TestCase):
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


if __name__ == "__main__":
    unittest.main()
