from pathlib import Path

from .code_generator import get_array_type, get_msg_pkg, get_msg_type, is_array, is_primitive, is_string


class SizeRegistryGenerator:
    def __init__(self):
        pass

    def _collect_entries(self, output_root_dir: Path):
        pdu_size_dir = output_root_dir / 'pdu_size'
        entries = []
        if not pdu_size_dir.exists():
            return entries

        for pkg_dir in sorted(pdu_size_dir.iterdir()):
            if not pkg_dir.is_dir():
                continue
            pkg_name = pkg_dir.name
            for size_file in sorted(pkg_dir.glob("*.txt")):
                msg_name = size_file.stem
                try:
                    size = int(size_file.read_text().strip())
                except ValueError:
                    continue
                entries.append({
                    "type_name": f"{pkg_name}/{msg_name}",
                    "size": size
                })
        return entries

    def _emit_c_registry(self, output_root_dir: Path, entries):
        types_dir = output_root_dir / 'types'
        types_dir.mkdir(parents=True, exist_ok=True)
        header_path = types_dir / 'pdu_size_registry.h'
        source_path = types_dir / 'pdu_size_registry.c'

        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        header = [
            "#ifndef HAKO_PDU_SIZE_REGISTRY_H",
            "#define HAKO_PDU_SIZE_REGISTRY_H",
            "",
            "#include <stdint.h>",
            "#include <stddef.h>",
            "",
            "#ifdef __cplusplus",
            "extern \"C\" {",
            "#endif",
            "",
            "typedef struct {",
            "    const char* type_name;",
            "    uint32_t size;",
            "} HakoPduSizeEntry;",
            "",
            "const HakoPduSizeEntry* hako_pdu_size_table(void);",
            "size_t hako_pdu_size_count(void);",
            "int hako_pdu_get_size(const char* type_name, uint32_t* out_size);",
            "",
            "#ifdef __cplusplus",
            "}",
            "#endif",
            "",
            "#endif /* HAKO_PDU_SIZE_REGISTRY_H */",
            ""
        ]
        header_path.write_text("\n".join(header), encoding="utf-8")

        lines = [
            "#include \"pdu_size_registry.h\"",
            "#include <string.h>",
            "",
            "static const HakoPduSizeEntry g_pdu_size_table[] = {"
        ]
        for entry in entries_sorted:
            lines.append(f"    {{ \"{entry['type_name']}\", {entry['size']} }},")
        lines.append("};")
        lines.append("")
        lines.append("const HakoPduSizeEntry* hako_pdu_size_table(void) {")
        lines.append("    return g_pdu_size_table;")
        lines.append("}")
        lines.append("")
        lines.append("size_t hako_pdu_size_count(void) {")
        lines.append("    return sizeof(g_pdu_size_table) / sizeof(g_pdu_size_table[0]);")
        lines.append("}")
        lines.append("")
        lines.append("int hako_pdu_get_size(const char* type_name, uint32_t* out_size) {")
        lines.append("    if (type_name == NULL || out_size == NULL) {")
        lines.append("        return -1;")
        lines.append("    }")
        lines.append("    size_t left = 0;")
        lines.append("    size_t right = hako_pdu_size_count();")
        lines.append("    while (left < right) {")
        lines.append("        size_t mid = left + (right - left) / 2;")
        lines.append("        int cmp = strcmp(type_name, g_pdu_size_table[mid].type_name);")
        lines.append("        if (cmp == 0) {")
        lines.append("            *out_size = g_pdu_size_table[mid].size;")
        lines.append("            return 0;")
        lines.append("        }")
        lines.append("        if (cmp < 0) {")
        lines.append("            right = mid;")
        lines.append("        } else {")
        lines.append("            left = mid + 1;")
        lines.append("        }")
        lines.append("    }")
        lines.append("    return -1;")
        lines.append("}")
        lines.append("")
        source_path.write_text("\n".join(lines), encoding="utf-8")

    def _emit_python_registry(self, output_root_dir: Path, entries):
        python_dir = output_root_dir / 'python'
        python_dir.mkdir(parents=True, exist_ok=True)
        py_path = python_dir / 'pdu_size.py'
        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        lines = [
            "# Auto-generated PDU size registry",
            "PDU_SIZE = {"
        ]
        for entry in entries_sorted:
            lines.append(f"    \"{entry['type_name']}\": {entry['size']},")
        lines.append("}")
        lines.append("")
        lines.append("def get_size(type_name: str):")
        lines.append("    return PDU_SIZE.get(type_name)")
        lines.append("")
        py_path.write_text("\n".join(lines), encoding="utf-8")

    def _emit_javascript_registry(self, output_root_dir: Path, entries):
        javascript_dir = output_root_dir / 'javascript'
        javascript_dir.mkdir(parents=True, exist_ok=True)
        js_path = javascript_dir / 'pdu_size.js'
        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        lines = [
            "// Auto-generated PDU size registry",
            "export const PDU_SIZE = {"
        ]
        for entry in entries_sorted:
            lines.append(f"  \"{entry['type_name']}\": {entry['size']},")
        lines.append("};")
        lines.append("")
        lines.append("export function getSize(typeName) {")
        lines.append("  return PDU_SIZE[typeName];")
        lines.append("}")
        lines.append("")
        js_path.write_text("\n".join(lines), encoding="utf-8")

    def generate(self, output_root_dir: Path):
        entries = self._collect_entries(output_root_dir)
        self._emit_c_registry(output_root_dir, entries)
        self._emit_python_registry(output_root_dir, entries)
        self._emit_javascript_registry(output_root_dir, entries)


class CdrSizeRegistryGenerator:
    PRIMITIVE_LAYOUT = {
        "bool": (1, 1),
        "byte": (1, 1),
        "char": (1, 1),
        "int8": (1, 1),
        "uint8": (1, 1),
        "int16": (2, 2),
        "uint16": (2, 2),
        "int32": (4, 4),
        "uint32": (4, 4),
        "float32": (4, 4),
        "int64": (8, 8),
        "uint64": (8, 8),
        "float64": (8, 8),
    }

    def _align(self, offset, alignment):
        return offset + ((alignment - (offset % alignment)) % alignment)

    def _field_size(self, type_name, current_pkg, message_cache, offset):
        if is_array(type_name):
            base_type = get_array_type(type_name)
            array_size = self._array_size(type_name)
            if array_size is None:
                offset = self._align(offset, 4)
                return offset + 4

            for _ in range(array_size):
                offset = self._field_size(base_type, current_pkg, message_cache, offset)
            return offset

        if is_string(type_name):
            offset = self._align(offset, 4)
            # Empty CDR string: uint32 length plus null terminator.
            return offset + 4 + 1

        if is_primitive(type_name):
            size, alignment = self.PRIMITIVE_LAYOUT[type_name]
            offset = self._align(offset, alignment)
            return offset + size

        msg_pkg = get_msg_pkg(type_name, current_pkg)
        msg_name = get_msg_type(type_name)
        msg_def = message_cache[f"{msg_pkg}/{msg_name}"]
        return self._body_size(msg_def, message_cache, offset)

    def _array_size(self, type_name):
        size_str = type_name.split('[', 1)[1].split(']', 1)[0]
        if size_str == "":
            return None
        return int(size_str)

    def _body_size(self, msg_def, message_cache, offset=0):
        for field in msg_def.get("fields", []):
            offset = self._field_size(field["type"], msg_def["package"], message_cache, offset)
        return offset

    def _collect_entries(self, message_cache):
        entries = []
        for package_msg in sorted(message_cache):
            msg_def = message_cache[package_msg]
            body_size = self._body_size(msg_def, message_cache)
            entries.append({
                "type_name": f"{msg_def['package']}/{msg_def['message']}",
                "size": body_size + 4,
            })
        return entries

    def _emit_python_registry(self, output_root_dir: Path, entries):
        python_dir = output_root_dir / 'python'
        python_dir.mkdir(parents=True, exist_ok=True)
        py_path = python_dir / 'pdu_cdr_size.py'
        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        lines = [
            "# Auto-generated CDR minimum payload size registry",
            "# Sizes include the 4-byte CDR encapsulation header.",
            "# Variable-length sequences are counted as length 0; strings are counted as empty strings.",
            "PDU_CDR_SIZE = {"
        ]
        for entry in entries_sorted:
            lines.append(f"    \"{entry['type_name']}\": {entry['size']},")
        lines.append("}")
        lines.append("")
        lines.append("def get_size(type_name: str):")
        lines.append("    return PDU_CDR_SIZE.get(type_name)")
        lines.append("")
        py_path.write_text("\n".join(lines), encoding="utf-8")

    def _emit_javascript_registry(self, output_root_dir: Path, entries):
        javascript_dir = output_root_dir / 'javascript'
        javascript_dir.mkdir(parents=True, exist_ok=True)
        js_path = javascript_dir / 'pdu_cdr_size.js'
        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        lines = [
            "// Auto-generated CDR minimum payload size registry",
            "// Sizes include the 4-byte CDR encapsulation header.",
            "// Variable-length sequences are counted as length 0; strings are counted as empty strings.",
            "export const PDU_CDR_SIZE = {"
        ]
        for entry in entries_sorted:
            lines.append(f"  \"{entry['type_name']}\": {entry['size']},")
        lines.append("};")
        lines.append("")
        lines.append("export function getSize(typeName) {")
        lines.append("  return PDU_CDR_SIZE[typeName];")
        lines.append("}")
        lines.append("")
        js_path.write_text("\n".join(lines), encoding="utf-8")

    def _emit_c_registry(self, output_root_dir: Path, entries):
        types_dir = output_root_dir / 'types'
        types_dir.mkdir(parents=True, exist_ok=True)
        header_path = types_dir / 'pdu_cdr_size_registry.h'
        source_path = types_dir / 'pdu_cdr_size_registry.c'
        entries_sorted = sorted(entries, key=lambda x: x["type_name"])

        header = [
            "#ifndef HAKO_PDU_CDR_SIZE_REGISTRY_H",
            "#define HAKO_PDU_CDR_SIZE_REGISTRY_H",
            "",
            "#include <stdint.h>",
            "#include <stddef.h>",
            "",
            "#ifdef __cplusplus",
            "extern \"C\" {",
            "#endif",
            "",
            "typedef struct {",
            "    const char* type_name;",
            "    uint32_t size;",
            "} HakoPduCdrSizeEntry;",
            "",
            "const HakoPduCdrSizeEntry* hako_pdu_cdr_size_table(void);",
            "size_t hako_pdu_cdr_size_count(void);",
            "int hako_pdu_cdr_get_size(const char* type_name, uint32_t* out_size);",
            "",
            "#ifdef __cplusplus",
            "}",
            "#endif",
            "",
            "#endif /* HAKO_PDU_CDR_SIZE_REGISTRY_H */",
            ""
        ]
        header_path.write_text("\n".join(header), encoding="utf-8")

        lines = [
            "#include \"pdu_cdr_size_registry.h\"",
            "#include <string.h>",
            "",
            "static const HakoPduCdrSizeEntry g_pdu_cdr_size_table[] = {"
        ]
        for entry in entries_sorted:
            lines.append(f"    {{ \"{entry['type_name']}\", {entry['size']} }},")
        lines.append("};")
        lines.append("")
        lines.append("const HakoPduCdrSizeEntry* hako_pdu_cdr_size_table(void) {")
        lines.append("    return g_pdu_cdr_size_table;")
        lines.append("}")
        lines.append("")
        lines.append("size_t hako_pdu_cdr_size_count(void) {")
        lines.append("    return sizeof(g_pdu_cdr_size_table) / sizeof(g_pdu_cdr_size_table[0]);")
        lines.append("}")
        lines.append("")
        lines.append("int hako_pdu_cdr_get_size(const char* type_name, uint32_t* out_size) {")
        lines.append("    if (type_name == NULL || out_size == NULL) {")
        lines.append("        return -1;")
        lines.append("    }")
        lines.append("    size_t left = 0;")
        lines.append("    size_t right = hako_pdu_cdr_size_count();")
        lines.append("    while (left < right) {")
        lines.append("        size_t mid = left + (right - left) / 2;")
        lines.append("        int cmp = strcmp(type_name, g_pdu_cdr_size_table[mid].type_name);")
        lines.append("        if (cmp == 0) {")
        lines.append("            *out_size = g_pdu_cdr_size_table[mid].size;")
        lines.append("            return 0;")
        lines.append("        }")
        lines.append("        if (cmp < 0) {")
        lines.append("            right = mid;")
        lines.append("        } else {")
        lines.append("            left = mid + 1;")
        lines.append("        }")
        lines.append("    }")
        lines.append("    return -1;")
        lines.append("}")
        lines.append("")
        source_path.write_text("\n".join(lines), encoding="utf-8")

    def generate(self, output_root_dir: Path, message_cache):
        entries = self._collect_entries(message_cache)
        self._emit_c_registry(output_root_dir, entries)
        self._emit_python_registry(output_root_dir, entries)
        self._emit_javascript_registry(output_root_dir, entries)
