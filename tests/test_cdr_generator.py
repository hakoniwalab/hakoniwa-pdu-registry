import tempfile
import struct
import sys
import importlib
import json
import shutil
import subprocess
import unittest
from contextlib import redirect_stdout
from io import StringIO
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator
from generators.generate_hako_pdu_msgs.dependency_resolver import DependencyResolver
from generators.generate_hako_pdu_msgs.offset_parser import PduOffsetEntry, parse_offset_file
from generators.generate_hako_pdu_msgs.size_registry_generator import CdrSizeRegistryGenerator


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

    def test_generator_rejects_wstring_even_for_direct_message_cache(self):
        message_cache = {
            "sample_msgs/Unsupported": {
                "package": "sample_msgs",
                "message": "Unsupported",
                "fields": [{"name": "value", "type": "wstring"}],
            }
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            with self.assertRaisesRegex(ValueError, "wstring wire representation"):
                CodeGenerator("template").generate_all(message_cache, {}, Path(tmpdir))

    def test_byte_and_char_generate_uint8_public_types(self):
        message_cache = {
            "sample_msgs/Aliases": {
                "package": "sample_msgs",
                "message": "Aliases",
                "fields": [
                    {"name": "byte_value", "type": "byte"},
                    {"name": "char_value", "type": "char"},
                    {"name": "byte_array", "type": "byte[2]"},
                    {"name": "char_array", "type": "char[]"},
                ],
            }
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir)
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)

            py_type = (
                output_dir / "python/sample_msgs/pdu_pytype_Aliases.py"
            ).read_text(encoding="utf-8")
            js_type = (
                output_dir / "javascript/sample_msgs/pdu_jstype_Aliases.js"
            ).read_text(encoding="utf-8")
            ruby_type = (
                output_dir / "ruby/sample_msgs/pdu_type_Aliases.rb"
            ).read_text(encoding="utf-8")
            elixir_type = (
                output_dir / "elixir/sample_msgs/pdu_type_Aliases.ex"
            ).read_text(encoding="utf-8")

            char_definition = {
                "package": "std_msgs",
                "message": "Char",
                "fields": [{"name": "data", "type": "char"}],
            }
            offsets = parse_offset_file(Path("pdu/offset/std_msgs/Char.offset"))
            generator = CodeGenerator("template")
            with redirect_stdout(StringIO()):
                generator.generate_ruby_converter(char_definition, offsets, output_dir)
                generator.generate_elixir_converter(char_definition, offsets, output_dir)
            ruby_converter = (
                output_dir / "ruby/std_msgs/pdu_conv_Char.rb"
            ).read_text(encoding="utf-8")
            elixir_converter = (
                output_dir / "elixir/std_msgs/pdu_conv_Char.ex"
            ).read_text(encoding="utf-8")

            self.assertIn("byte_value: int", py_type)
            self.assertIn("char_value: int", py_type)
            self.assertIn("char_array: List[int]", py_type)
            self.assertIn("@type { number }", js_type)
            self.assertIn("@type { Array<number> }", js_type)
            self.assertIn("byte_value: 0", ruby_type)
            self.assertIn("char_value: 0", ruby_type)
            self.assertIn("byte_value: 0", elixir_type)
            self.assertIn("char_value: 0", elixir_type)
            self.assertIn("when 'byte', 'char', 'uint8'", ruby_converter)
            self.assertNotIn(".chr", ruby_converter)
            self.assertIn('"char" -> <<value::unsigned-integer-size(8)>>', elixir_converter)
            self.assertNotIn("string_first_byte", elixir_converter)

    def test_byte_and_char_scalar_fixed_and_variable_arrays_roundtrip(self):
        message_definition = {
            "package": "sample_msgs",
            "message": "PrimitiveAliases",
            "fields": [
                {"name": "byte_scalar", "type": "byte"},
                {"name": "char_scalar", "type": "char"},
                {"name": "byte_fixed", "type": "byte[3]"},
                {"name": "char_fixed", "type": "char[3]"},
                {"name": "byte_variable", "type": "byte[]"},
                {"name": "char_variable", "type": "char[]"},
            ],
        }
        offsets = [
            PduOffsetEntry("single", "primitive", "byte_scalar", "byte", 0, 1, 1),
            PduOffsetEntry("single", "primitive", "char_scalar", "char", 1, 1, 1),
            PduOffsetEntry("array", "primitive", "byte_fixed", "byte", 2, 3, 3),
            PduOffsetEntry("array", "primitive", "char_fixed", "char", 5, 3, 3),
            PduOffsetEntry("varray", "primitive", "byte_variable", "byte", 8, 1, 8),
            PduOffsetEntry("varray", "primitive", "char_variable", "char", 16, 1, 8),
        ]
        expected = {
            "byte_scalar": 255,
            "char_scalar": 254,
            "byte_fixed": [0, 127, 255],
            "char_fixed": [1, 128, 254],
            "byte_variable": [255, 2, 0, 200],
            "char_variable": [3, 253],
        }

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "generated_contract"
            generator = CodeGenerator("template")
            with redirect_stdout(StringIO()):
                generator.generate_all(
                    {"sample_msgs/PrimitiveAliases": message_definition}, {}, output_dir
                )
                generator.generate_python_converter(message_definition, offsets, output_dir)
                generator.generate_javascript_converter(message_definition, offsets, output_dir)
                generator.generate_ruby_converter(message_definition, offsets, output_dir)
                generator.generate_elixir_converter(message_definition, offsets, output_dir)

            shutil.copy2("pdu/python/pdu_utils.py", output_dir / "python/pdu_utils.py")
            shutil.copy2("pdu/python/binary_io.py", output_dir / "python/binary_io.py")
            shutil.copy2(
                "pdu/javascript/pdu_utils.js", output_dir / "javascript/pdu_utils.js"
            )

            self._assert_python_alias_array_roundtrip(output_dir, expected)
            self._assert_javascript_alias_array_roundtrip(output_dir, expected)
            self._assert_ruby_alias_array_roundtrip(output_dir, expected)
            self._assert_elixir_alias_array_roundtrip(output_dir, expected)

    def _assert_python_alias_array_roundtrip(self, output_dir, expected):
        for directory in (
            output_dir,
            output_dir / "python",
            output_dir / "python" / "sample_msgs",
        ):
            (directory / "__init__.py").touch()

        sys.path.insert(0, str(output_dir.parent))
        try:
            type_module = importlib.import_module(
                "generated_contract.python.sample_msgs.pdu_pytype_PrimitiveAliases"
            )
            converter = importlib.import_module(
                "generated_contract.python.sample_msgs.pdu_conv_PrimitiveAliases"
            )
            value = type_module.PrimitiveAliases()
            for name, field_value in expected.items():
                setattr(value, name, field_value)
            restored = converter.pdu_to_py_PrimitiveAliases(
                converter.py_to_pdu_PrimitiveAliases(value)
            )
            for name, field_value in expected.items():
                actual = getattr(restored, name)
                self.assertEqual(list(actual) if isinstance(field_value, list) else actual, field_value)
        finally:
            sys.path.remove(str(output_dir.parent))
            for module_name in list(sys.modules):
                if module_name == "generated_contract" or module_name.startswith(
                    "generated_contract."
                ):
                    sys.modules.pop(module_name)

    def _assert_javascript_alias_array_roundtrip(self, output_dir, expected):
        if shutil.which("node") is None:
            return
        (output_dir / "package.json").write_text(
            '{"type":"module"}\n', encoding="utf-8"
        )
        converter_uri = (
            output_dir / "javascript/sample_msgs/pdu_conv_PrimitiveAliases.js"
        ).as_uri()
        type_uri = (
            output_dir / "javascript/sample_msgs/pdu_jstype_PrimitiveAliases.js"
        ).as_uri()
        script = f"""
import {{ PrimitiveAliases }} from {json.dumps(type_uri)};
import {{ jsToPdu_PrimitiveAliases, pduToJs_PrimitiveAliases }} from {json.dumps(converter_uri)};
const expected = {json.dumps(expected)};
const value = Object.assign(new PrimitiveAliases(), expected);
const restored = pduToJs_PrimitiveAliases(jsToPdu_PrimitiveAliases(value));
for (const [name, wanted] of Object.entries(expected)) {{
  const actual = Array.isArray(wanted) ? Array.from(restored[name]) : restored[name];
  if (JSON.stringify(actual) !== JSON.stringify(wanted)) throw new Error(`${{name}} mismatch`);
}}
"""
        subprocess.run(
            ["node", "--input-type=module", "-e", script], check=True
        )

    def _assert_ruby_alias_array_roundtrip(self, output_dir, expected):
        if shutil.which("ruby") is None:
            return
        converter = output_dir / "ruby/sample_msgs/pdu_conv_PrimitiveAliases.rb"
        assignments = ", ".join(
            f"{name}: {repr(value).replace('[', '[').replace(']', ']')}"
            for name, value in expected.items()
        )
        assertions = "; ".join(
            f"abort('{name} mismatch') unless restored.{name} == {repr(value)}"
            for name, value in expected.items()
        )
        script = (
            f"require {str(converter.with_suffix(''))!r}; "
            f"value=HakoPdu::SampleMsgs::PrimitiveAliases.new({assignments}); "
            "binary=HakoPdu::SampleMsgs::PrimitiveAliasesConverter.ruby_to_pdu_primitive_aliases(value); "
            "restored=HakoPdu::SampleMsgs::PrimitiveAliasesConverter.pdu_to_ruby_primitive_aliases(binary); "
            f"{assertions}"
        )
        subprocess.run(["ruby", "-e", script], check=True)

    def _assert_elixir_alias_array_roundtrip(self, output_dir, expected):
        if shutil.which("elixir") is None:
            return
        type_file = output_dir / "elixir/sample_msgs/pdu_type_PrimitiveAliases.ex"
        converter_file = output_dir / "elixir/sample_msgs/pdu_conv_PrimitiveAliases.ex"
        pairs = ", ".join(f"{name}: {repr(value)}" for name, value in expected.items())
        checks = "; ".join(
            f"if restored.{name} != {repr(value)}, do: System.halt(1)"
            for name, value in expected.items()
        )
        script = (
            f"value=HakoPdu.SampleMsgs.PrimitiveAliases.new(%{{{pairs}}}); "
            "binary=HakoPdu.SampleMsgs.PrimitiveAliasesConverter.elixir_to_pdu_primitive_aliases(value); "
            "restored=HakoPdu.SampleMsgs.PrimitiveAliasesConverter.pdu_to_elixir_primitive_aliases(binary); "
            f"{checks}"
        )
        subprocess.run(
            ["elixir", "-r", str(type_file), "-r", str(converter_file), "-e", script],
            check=True,
        )

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

    def test_generates_javascript_cdr_converter_and_runtime(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/GameControllerOperation"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "pdu"
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_all(message_cache, {}, output_dir)

            runtime = output_dir / "javascript" / "pdu_cdr_runtime.js"
            converter = output_dir / "javascript" / "hako_msgs" / "pdu_cdr_conv_GameControllerOperation.js"
            self.assertTrue(runtime.exists())
            self.assertTrue(converter.exists())

            text = converter.read_text(encoding="utf-8")
            self.assertIn("class PduGameControllerOperationConverter", text)
            self.assertIn("to_cdr", text)
            self.assertIn("from_cdr", text)

    def test_generate_cdr_emits_only_cdr_related_artifacts(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/GameControllerOperation"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "pdu"
            with redirect_stdout(StringIO()):
                CodeGenerator("template").generate_cdr(message_cache, {}, output_dir)

            self.assertTrue((output_dir / "types" / "pdu_cdr_runtime.hpp").exists())
            self.assertTrue((output_dir / "types" / "hako_msgs" / "pdu_cpptype_GameControllerOperation.hpp").exists())
            self.assertTrue((output_dir / "types" / "hako_msgs" / "pdu_cpptype_cdr_conv_GameControllerOperation.hpp").exists())
            self.assertTrue((output_dir / "python" / "pdu_cdr_runtime.py").exists())
            self.assertTrue((output_dir / "python" / "hako_msgs" / "pdu_cdr_conv_GameControllerOperation.py").exists())
            self.assertTrue((output_dir / "javascript" / "pdu_cdr_runtime.js").exists())
            self.assertTrue((output_dir / "javascript" / "hako_msgs" / "pdu_cdr_conv_GameControllerOperation.js").exists())
            self.assertFalse((output_dir / "offset").exists())
            self.assertFalse((output_dir / "javascript" / "hako_msgs" / "pdu_conv_GameControllerOperation.js").exists())

    def test_generates_cdr_minimum_size_registries(self):
        resolver = DependencyResolver(["idl"])
        message_cache = resolver.get_all_dependencies(["hako_msgs/GameControllerOperation"])

        with tempfile.TemporaryDirectory() as tmpdir:
            output_dir = Path(tmpdir) / "pdu"
            CdrSizeRegistryGenerator().generate(output_dir, message_cache)

            c_header = output_dir / "types" / "pdu_cdr_size_registry.h"
            c_source = output_dir / "types" / "pdu_cdr_size_registry.c"
            py_registry = output_dir / "python" / "pdu_cdr_size.py"
            js_registry = output_dir / "javascript" / "pdu_cdr_size.js"
            self.assertTrue(c_header.exists())
            self.assertTrue(c_source.exists())
            self.assertTrue(py_registry.exists())
            self.assertTrue(js_registry.exists())

            c_header_text = c_header.read_text(encoding="utf-8")
            c_source_text = c_source.read_text(encoding="utf-8")
            py_text = py_registry.read_text(encoding="utf-8")
            js_text = js_registry.read_text(encoding="utf-8")
            self.assertIn("hako_pdu_cdr_get_size", c_header_text)
            self.assertIn('{ "hako_msgs/GameControllerOperation", 67 }', c_source_text)
            self.assertIn('"hako_msgs/GameControllerOperation": 67', py_text)
            self.assertIn('"hako_msgs/GameControllerOperation": 67', js_text)


if __name__ == "__main__":
    unittest.main()
