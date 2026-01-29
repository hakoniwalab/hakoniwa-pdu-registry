from pathlib import Path


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
