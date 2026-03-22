import os
import re
from pathlib import Path
import jinja2
from collections import OrderedDict

def _collect_dependencies(pkg_msg, message_cache, root_pkg,
                          visited,  # set[str]
                          includes, csharp_includes,
                          cpp_includes, conv_includes, conv_cpp_includes, py_imports, js_imports):
    if pkg_msg in visited:
        return
    visited.add(pkg_msg)

    msg_def = message_cache[pkg_msg]
    for field in msg_def.get('fields', []):
        ftype = field['type']
        if is_primitive(ftype) or is_string(ftype):
            continue

        base = get_array_type(ftype)
        dep_pkg_msg = f"{msg_def['package']}/{base}" if '/' not in base else base
        if dep_pkg_msg not in message_cache:
            #print(f"Warning: Dependency {dep_pkg_msg} not found in message cache. Skipping.")
            #print(f"arguments: {pkg_msg}, {root_pkg}, {visited}, {includes}, {csharp_includes}, {cpp_includes}, {conv_includes}, {conv_cpp_includes}, {py_imports}, {js_imports}")
            continue

        dep_pkg, dep_msg = dep_pkg_msg.split('/')

        # ───── include/import 群に追加（順序保持したいので OrderedDict を使う）─────
        includes[f"{dep_pkg}/pdu_ctype_{dep_msg}.h"] = None
        cpp_includes[f"{dep_pkg}/pdu_cpptype_{dep_msg}.hpp"] = None
        conv_includes[f"{dep_pkg}/pdu_ctype_conv_{dep_msg}.hpp"] = None
        conv_cpp_includes[f"{dep_pkg}/pdu_cpptype_conv_{dep_msg}.hpp"] = None
        py_imports[dep_pkg_msg] = {
            'dep_pkg': dep_pkg,
            'file': f"pdu_pytype_{dep_msg}",
            'class_name': get_python_class_name(dep_msg)
        }
        js_imports[dep_pkg_msg] = {
            'dep_pkg': dep_pkg,
            'file': f"pdu_jstype_{dep_msg}",
            'class_name': get_js_class_name(dep_msg)
        }
        if dep_pkg != root_pkg:
            csharp_includes[dep_pkg] = None

        # ───── さらに再帰 ─────
        _collect_dependencies(dep_pkg_msg, message_cache, root_pkg,
                              visited, includes, csharp_includes,
                              cpp_includes, conv_includes, conv_cpp_includes, py_imports, js_imports)
# --- テンプレートヘルパー関数群 (generate.pyの挙動を完全に模倣) ---

ROS_PRIMITIVE_TYPES_FOR_TEMPLATE = [
    'bool', 'byte', 'char', 'float32', 'float64', 'int8', 'uint8',
    'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64'
]

def get_array_type(name):
    return name.split('[', 1)[0].strip()

def is_primitive(name):
    return name in ROS_PRIMITIVE_TYPES_FOR_TEMPLATE

def is_string(name):
	if (name == 'string'):
		return True
	else:
		return False

def is_array(name):
    return '[' in name

def is_primitive_array(name):
    return is_array(name) and is_primitive(get_array_type(name))

def is_string_array(name):
    return is_array(name) and is_string(get_array_type(name))

def get_struct_array_type(name):
    return name.split('[', 1)[0].strip()

def get_type(name):
    if is_array(name):
        return get_array_type(name)
    return name

def get_msg_type(name):
    name = get_array_type(name)
    if '/' in name:
        tmp = name.split('/')[1]
    else:
        tmp = name
    if tmp == 'time':
        return 'Time'
    return tmp

def get_msg_pkg(name, default_pkg):
    name = get_array_type(name)
    if '/' in name:
        return name.split('/')[0]
    return default_pkg

def convert_snake(name):
    if name == "TFMessage":
        return "tf_message"
    s0 = name[0].lower()
    s1n = name[1:]
    cs1n = re.sub("([A-Z])", lambda x: "_" + x.group(1).lower(), s1n)
    return s0 + cs1n

def get_csharp_type(name):
    type_map = {
        "byte": "byte", "char": "byte", "int8": "sbyte", "uint8": "byte",
        "int16": "short", "uint16": "ushort", "int32": "int", "uint32": "uint",
        "int64": "long", "uint64": "ulong", "float32": "float",
        "float64": "double", "bool": "bool", "string": "string"
    }
    return type_map.get(get_array_type(name), get_msg_type(name))

def get_csharp_v2_type_hint(name):
    base_type = get_array_type(name)
    cs_type = get_csharp_type(base_type)
    if is_array(name):
        return f"List<{cs_type}>"
    return cs_type

def get_csharp_v2_default_value(name):
    if is_array(name):
        return f"new {get_csharp_v2_type_hint(name)}()"
    if is_primitive(name):
        if name == 'float32':
            return "0.0F"
        if name == 'float64':
            return "0.0"
        if name == 'bool':
            return "false"
        return "0"
    if is_string(name):
        return 'string.Empty'
    return f"new {get_msg_type(name)}()"

def get_csharp_io_suffix(name):
    suffix_map = {
        "bool": "Bool",
        "byte": "UInt8",
        "char": "UInt8",
        "int8": "Int8",
        "uint8": "UInt8",
        "int16": "Int16",
        "uint16": "UInt16",
        "int32": "Int32",
        "uint32": "UInt32",
        "int64": "Int64",
        "uint64": "UInt64",
        "float32": "Float32",
        "float64": "Float64",
        "string": "String",
    }
    return suffix_map[get_array_type(name)]

def get_godot_io_suffix(name):
    suffix_map = {
        "bool": "Bool",
        "byte": "UInt8",
        "char": "UInt8",
        "int8": "Int8",
        "uint8": "UInt8",
        "int16": "Int16",
        "uint16": "UInt16",
        "int32": "Int32",
        "uint32": "UInt32",
        "int64": "Int64",
        "uint64": "UInt64",
        "float32": "Float32",
        "float64": "Float64",
        "string": "String",
    }
    return suffix_map[get_array_type(name)]

# --- Python用ヘルパー関数 ---
def get_python_class_name(name):
    return get_msg_type(name)

def get_python_type_hint(name):
    type_map = {
        "bool": "bool", "byte": "int", "char": "str",
        "float32": "float", "float64": "float",
        "int8": "int", "uint8": "int",
        "int16": "int", "uint16": "int",
        "int32": "int", "uint32": "int",
        "int64": "int", "uint64": "int",
        "string": "str"
    }
    base_type = get_array_type(name)
    py_type = type_map.get(base_type, get_python_class_name(base_type))

    if is_array(name):
        return f"List[{py_type}]"
    return py_type

def get_python_default_value(name):
    if is_array(name):
        return "[]"
    if is_primitive(name):
        if name in ['float32', 'float64']:
            return "0.0"
        elif name == 'bool':
            return "False"
        else:
            return "0"
    if is_string(name):
        return '""'
    # 構造体の場合はクラスのインスタンス化
    return f"{get_python_class_name(name)}()"

# --- JavaScript用ヘルパー関数 ---
def get_js_class_name(name):
    return get_msg_type(name)

def get_js_type_hint(name):
    type_map = {
        "bool": "boolean", "byte": "number", "char": "string",
        "float32": "number", "float64": "number",
        "int8": "number", "uint8": "number",
        "int16": "number", "uint16": "number",
        "int32": "number", "uint32": "number",
        "int64": "bigint", "uint64": "bigint",
        "string": "string"
    }
    base_type = get_array_type(name)
    js_type = type_map.get(base_type, get_js_class_name(base_type))

    if is_array(name):
        return f"Array<{js_type}>"
    return js_type

def get_js_default_value(name):
    if is_array(name):
        return "[]"
    if is_primitive(name):
        if name in ['int64', 'uint64']:
            return "0n"
        elif name in ['float32', 'float64']:
            return "0.0"
        elif name == 'bool':
            return "false"
        else:
            return "0"
    if is_string(name):
        return '""'
    # 構造体：インスタンス化して返す（nullにしない）
    return f"new {get_js_class_name(name)}()"


# --- Godot / GDScript用ヘルパー関数 ---
def get_godot_class_name(name):
    return get_msg_type(name)

def get_godot_global_class_name(pkg_name, msg_name):
    return f"HakoPdu_{pkg_name}_{msg_name}"

def get_godot_type_hint_with_pkg(name, default_pkg):
    base_type = get_array_type(name)
    if is_array(name):
        if is_string(base_type):
            return "Array[String]"
        if is_primitive(base_type):
            return get_godot_type_hint(name)
        return "Array"
    if is_primitive(base_type) or is_string(base_type):
        return get_godot_type_hint(base_type)
    return get_godot_global_class_name(get_msg_pkg(base_type, default_pkg), get_msg_type(base_type))

def get_godot_type_hint(name):
    type_map = {
        "bool": "bool",
        "byte": "int",
        "char": "int",
        "float32": "float",
        "float64": "float",
        "int8": "int",
        "uint8": "int",
        "int16": "int",
        "uint16": "int",
        "int32": "int",
        "uint32": "int",
        "int64": "int",
        "uint64": "int",
        "string": "String",
    }
    packed_array_map = {
        "byte": "PackedByteArray",
        "char": "PackedByteArray",
        "uint8": "PackedByteArray",
        "int32": "PackedInt32Array",
        "int64": "PackedInt64Array",
        "float32": "PackedFloat32Array",
        "float64": "PackedFloat64Array",
    }
    base_type = get_array_type(name)
    if is_array(name):
        if is_string(base_type):
            return "Array[String]"
        if is_primitive(base_type):
            return packed_array_map.get(base_type, "Array")
        return "Array"
    return type_map.get(base_type, get_godot_class_name(base_type))

def get_godot_default_value(name):
    base_type = get_array_type(name)
    if is_array(name):
        if is_string(base_type):
            return "[]"
        if is_primitive(base_type):
            packed_defaults = {
                "byte": "PackedByteArray()",
                "char": "PackedByteArray()",
                "uint8": "PackedByteArray()",
                "int32": "PackedInt32Array()",
                "int64": "PackedInt64Array()",
                "float32": "PackedFloat32Array()",
                "float64": "PackedFloat64Array()",
            }
            return packed_defaults.get(base_type, "[]")
        return "[]"
    if is_primitive(name):
        if name == 'bool':
            return "false"
        if name in ['float32', 'float64']:
            return "0.0"
        return "0"
    if is_string(name):
        return '""'
    return f"{get_godot_class_name(name)}.new()"

def get_godot_default_value_with_pkg(name, default_pkg):
    base_type = get_array_type(name)
    if is_primitive(base_type) or is_string(base_type) or is_array(name):
        return get_godot_default_value(name)
    return f"{get_godot_global_class_name(get_msg_pkg(base_type, default_pkg), get_msg_type(base_type))}.new()"

def get_godot_cpp_array_container(name):
    base_type = get_array_type(name)
    packed_array_map = {
        "byte": "PackedByteArray",
        "char": "PackedByteArray",
        "uint8": "PackedByteArray",
        "int32": "PackedInt32Array",
        "int64": "PackedInt64Array",
        "float32": "PackedFloat32Array",
        "float64": "PackedFloat64Array",
    }
    if is_string(base_type):
        return "Array"
    if is_primitive(base_type):
        return packed_array_map.get(base_type, "Array")
    return "Array"


def get_struct_format(ros_type_name):
    """ROSのプリミティブ型名をPythonのstructモジュールのフォーマット文字に変換"""
    format_map = {
        'bool': '?',
        'byte': 'b',
        'char': 'c',
        'int8': 'b',
        'uint8': 'B',
        'int16': 'h',
        'uint16': 'H',
        'int32': 'i',
        'uint32': 'I',
        'int64': 'q',
        'uint64': 'Q',
        'float32': 'f',
        'float64': 'd',
        # stringは特別扱い
    }
    # ROSの表現（例: "uint8[3]"）から基本型（"uint8"）を抽出
    base_type = get_array_type(ros_type_name)
    return '<' + format_map.get(base_type, '') # Little-endianをデフォルトに

def get_base_data_size(offset_data):
    """オフセット情報からBaseDataの合計サイズを計算する"""
    if not offset_data:
        return 0
    # 最も大きいオフセットを持つエントリを見つける
    last_entry = max(offset_data, key=lambda x: x['offset'])
    # そのエントリの末尾がBaseDataのサイズとなる
    return last_entry['offset'] + last_entry['size']


# --- CodeGenerator クラス ---

class CodeGenerator:
    def __init__(self, template_dir):
        self.template_dir = Path(template_dir)

    def _render_template(self, template_name, context):
        template_path = self.template_dir / template_name
        with open(template_path, 'r', encoding='utf-8') as f:
            template_str = f.read()
        env = jinja2.Environment(loader=jinja2.FileSystemLoader(self.template_dir, encoding='utf8'))
        tpl = env.get_template(template_name)
        return tpl.render(context)

    def _prepare_context(self, package_msg, message_cache, varray_size_def):
        msg_def = message_cache[package_msg]
        root_pkg = msg_def['package']
        msg_name = msg_def['message']

        includes          = OrderedDict()
        csharp_includes   = OrderedDict()
        cpp_includes      = OrderedDict()
        conv_includes     = OrderedDict()
        conv_cpp_includes = OrderedDict()
        py_imports        = OrderedDict()
        js_imports        = OrderedDict()
        godot_imports     = OrderedDict()

        _collect_dependencies(package_msg, message_cache, root_pkg,
                          visited=set(),
                          includes=includes,
                          csharp_includes=csharp_includes,
                          cpp_includes=cpp_includes,
                          conv_includes=conv_includes,
                              conv_cpp_includes=conv_cpp_includes,
                              py_imports=py_imports,
                              js_imports=js_imports)

        for dep_pkg_msg, dep in js_imports.items():
            godot_imports[dep_pkg_msg] = {
                'dep_pkg': dep['dep_pkg'],
                'class_name': dep['class_name'],
            }

        def get_array_size(mem_name, type_name_from_tpl):
            try:
                return varray_size_def[root_pkg][msg_name][mem_name]
            except KeyError:
                if '[' in type_name_from_tpl and ']' in type_name_from_tpl:
                    size_str = type_name_from_tpl.split('[', 1)[1].split(']', 1)[0]
                    if size_str:
                        return size_str
                return None

        container = {
            'json_data': msg_def, 'pkg_name': root_pkg, 'msg_type_name': msg_name,
            'class_name': get_python_class_name(msg_name), # Default class name
            'includes': sorted(includes), 
            'csharp_includes': sorted(csharp_includes), 
            'cpp_includes': sorted(cpp_includes),
            'conv_includes': sorted(conv_includes), 
            'conv_cpp_includes': sorted(conv_cpp_includes),
            'py_imports': sorted(py_imports.values(), key=lambda x: x['class_name']),
            'js_imports': sorted(js_imports.values(), key=lambda x: x['class_name']),
            'godot_imports': sorted(godot_imports.values(), key=lambda x: (x['dep_pkg'], x['class_name'])),
            'is_primitive': is_primitive, 'is_string': is_string, 'is_array': is_array,
            'is_primitive_array': is_primitive_array, 'is_string_array': is_string_array,
            'get_array_type': get_array_type, 'get_struct_array_type': get_struct_array_type,
            'get_type': get_type, 'get_msg_type': get_msg_type,
            'get_msg_pkg': lambda name: get_msg_pkg(name, root_pkg),
            'get_array_size': get_array_size, 'convert_snake': convert_snake,
            'get_csharp_type': get_csharp_type,
            'get_csharp_v2_type_hint': get_csharp_v2_type_hint,
            'get_csharp_v2_default_value': get_csharp_v2_default_value,
            'get_csharp_io_suffix': get_csharp_io_suffix,
            'get_python_type_hint': get_python_type_hint,
            'get_python_default_value': get_python_default_value,
            'get_python_class_name': get_python_class_name,
            'get_js_type_hint': get_js_type_hint,
            'get_js_default_value': get_js_default_value,
            'get_js_class_name': get_js_class_name,
            'get_godot_type_hint': get_godot_type_hint,
            'get_godot_type_hint_with_pkg': lambda name: get_godot_type_hint_with_pkg(name, root_pkg),
            'get_godot_default_value': get_godot_default_value,
            'get_godot_default_value_with_pkg': lambda name: get_godot_default_value_with_pkg(name, root_pkg),
            'get_godot_class_name': get_godot_class_name,
            'get_godot_global_class_name': lambda pkg_name, msg_name: get_godot_global_class_name(pkg_name, msg_name),
            'get_godot_io_suffix': get_godot_io_suffix,
            'get_godot_cpp_array_container': get_godot_cpp_array_container,
            'godot_global_class_name': get_godot_global_class_name(root_pkg, msg_name),
            'get_struct_format': get_struct_format
        }
        return {'container': container}

    def _generate_file(self, context, template_name, output_dir, file_pattern, description):
        content = self._render_template(template_name, context)
        if not content.endswith('\n'):
            content += '\n'
        if not content.strip():
            return

        pkg_name = context['container']['pkg_name']
        msg_name = context['container']['msg_type_name']
        output_path = Path(output_dir) / pkg_name
        output_path.mkdir(parents=True, exist_ok=True)
        file_path = output_path / file_pattern.format(msg_name=msg_name)
        with open(file_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write(content)
        print(f"Generated {description}: {file_path}")

    def _generate_shared_file(self, context, template_name, output_path, description):
        content = self._render_template(template_name, context)
        if not content.endswith('\n'):
            content += '\n'
        output_path = Path(output_path)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write(content)
        print(f"Generated {description}: {output_path}")

    def generate_all(self, message_cache, varray_size_def, output_root_dir):
        types_dir = Path(output_root_dir) / 'types'
        csharp_dir = Path(output_root_dir) / 'csharp'
        csharp_v2_dir = Path(output_root_dir) / 'csharp_v2'
        python_dir = Path(output_root_dir) / 'python'
        javascript_dir = Path(output_root_dir) / 'javascript'
        godot_gd_dir = Path(output_root_dir) / 'godot_gd'
        godot_cpp_runtime_dir = Path(output_root_dir) / 'godot_cpp_runtime'

        shared_context = {'container': {}}
        self._generate_shared_file(shared_context, 'pdu_csharp_v2_runtime_cs.tpl', csharp_v2_dir / "PduRuntime.cs", "C# v2 runtime")
        self._generate_shared_file(shared_context, 'pdu_godot_runtime_hpp.tpl', godot_cpp_runtime_dir / "PduRuntime.hpp", "Godot C++ runtime")

        for package_msg in message_cache.keys():
            context = self._prepare_context(package_msg, message_cache, varray_size_def)
            # C/C++ and C#
            self._generate_file(context, 'pdu_ctypes_h.tpl', types_dir, "pdu_ctype_{msg_name}.h", "C header")
            self._generate_file(context, 'pdu_csharp_class.tpl', csharp_dir, "{msg_name}.cs", "C# class")
            self._generate_file(context, 'pdu_csharp_v2_type_cs.tpl', csharp_v2_dir, "pdu_type_{msg_name}.cs", "C# v2 type definition")
            self._generate_file(context, 'pdu_cpptypes_hpp.tpl', types_dir, "pdu_cpptype_{msg_name}.hpp", "C++ type header")
            self._generate_file(context, 'pdu_ctypes_conv_cpp.tpl', types_dir, "pdu_ctype_conv_{msg_name}.hpp", "C->C++ conv header")
            self._generate_file(context, 'pdu_cpptypes_conv_cpp.tpl', types_dir, "pdu_cpptype_conv_{msg_name}.hpp", "C++->C conv header")
            # Python
            self._generate_file(context, 'pdu_pytypes_py.tpl', python_dir, "pdu_pytype_{msg_name}.py", "Python type definition")
            # JavaScript
            self._generate_file(context, 'pdu_jstypes_js.tpl', javascript_dir, "pdu_jstype_{msg_name}.js", "JavaScript type definition")
            # Godot GDScript
            self._generate_file(context, 'pdu_godot_types_gd.tpl', godot_gd_dir, "{msg_name}.gd", "Godot GDScript type definition")

    def generate_javascript_converter(self, msg_def, offset_data, output_root_dir):
        javascript_dir = Path(output_root_dir) / 'javascript'
        pkg_name = msg_def['package']
        msg_name = msg_def['message']

        js_conv_imports = []
        added_imports = set()
        for item in offset_data:
            if item.data_type == 'struct':
                dep_pkg = get_msg_pkg(item.type_name, pkg_name)
                dep_msg = get_msg_type(item.type_name)
                if dep_msg not in added_imports:
                    js_conv_imports.append({
                        'dep_pkg': dep_pkg,
                        'file': f"pdu_conv_{dep_msg}",
                        'msg_type': dep_msg,
                        'type_name': item.type_name,
                        'class_name': get_js_class_name(dep_msg)
                    })
                    added_imports.add(dep_msg)

        context = {
            'container': {
                'pkg_name': pkg_name,
                'msg_type_name': msg_name,
                'class_name': get_js_class_name(msg_name),
                'offset_data': [o.to_dict() for o in offset_data],
                'js_conv_imports': js_conv_imports,
                'get_js_class_name': get_js_class_name,
                'get_msg_type': get_msg_type,
                'get_array_type': get_array_type,
                'is_primitive': is_primitive,
                'is_string': is_string,
                'is_array': is_array,
            }
        }
        self._generate_file(context, 'pdu_js_conv_js.tpl', javascript_dir, f"pdu_conv_{msg_name}.js", "JavaScript converter")

    def generate_python_converter(self, msg_def, offset_data, output_root_dir):
        python_dir = Path(output_root_dir) / 'python'
        pkg_name = msg_def['package']
        msg_name = msg_def['message']

        # コンバータテンプレート用のコンテキストを準備
        # _prepare_context と似ているが、offset_data を直接利用する
        py_conv_imports = []
        for item in offset_data:
            if item.data_type == 'struct':
                dep_pkg = get_msg_pkg(item.type_name, pkg_name)
                dep_msg = get_msg_type(item.type_name)
                py_conv_imports.append({
                    'dep_pkg': dep_pkg,
                    'file': f"pdu_conv_{dep_msg}",
                    'pdu_to_py_func': f"pdu_to_py_{dep_msg}",
                    'py_to_pdu_func': f"py_to_pdu_{dep_msg}",
                })
                #print(f"Adding Python converter import for {dep_pkg}/{dep_msg}")

        context = {
            'container': {
                'pkg_name': pkg_name,
                'msg_type_name': msg_name,
                'class_name': get_python_class_name(msg_name),
                'offset_data': [o.to_dict() for o in offset_data],
                'py_conv_imports': py_conv_imports,
                'get_struct_format': get_struct_format,
                'get_msg_type': get_msg_type,
                'get_base_data_size': lambda: get_base_data_size(context['container']['offset_data'])
            }
        }
        self._generate_file(context, 'pdu_py_conv_py.tpl', python_dir, f"pdu_conv_{msg_name}.py", "Python converter")

    def generate_csharp_v2_converter(self, msg_def, offset_data, output_root_dir):
        csharp_v2_dir = Path(output_root_dir) / 'csharp_v2'
        pkg_name = msg_def['package']
        msg_name = msg_def['message']

        cs_conv_imports = []
        added_imports = set()
        for item in offset_data:
            if item.data_type == 'struct':
                dep_pkg = get_msg_pkg(item.type_name, pkg_name)
                dep_msg = get_msg_type(item.type_name)
                if dep_pkg == pkg_name:
                    continue
                if dep_pkg not in added_imports:
                    cs_conv_imports.append({
                        'dep_pkg': dep_pkg,
                        'msg_type': dep_msg,
                    })
                    added_imports.add(dep_pkg)

        context = {
            'container': {
                'pkg_name': pkg_name,
                'msg_type_name': msg_name,
                'class_name': get_msg_type(msg_name),
                'offset_data': [o.to_dict() for o in offset_data],
                'cs_conv_imports': cs_conv_imports,
                'get_msg_type': get_msg_type,
                'get_array_type': get_array_type,
                'get_csharp_type': get_csharp_type,
                'get_csharp_v2_type_hint': get_csharp_v2_type_hint,
                'get_csharp_v2_default_value': get_csharp_v2_default_value,
                'get_csharp_io_suffix': get_csharp_io_suffix,
                'is_primitive': is_primitive,
                'is_string': is_string,
                'is_array': is_array,
            }
        }
        self._generate_file(context, 'pdu_csharp_v2_conv_cs.tpl', csharp_v2_dir, f"pdu_conv_{msg_name}.cs", "C# v2 converter")

    def generate_godot_cpp_converter(self, msg_def, offset_data, output_root_dir):
        godot_cpp_dir = Path(output_root_dir) / 'godot_cpp'
        pkg_name = msg_def['package']
        msg_name = msg_def['message']

        godot_cpp_imports = []
        added_imports = set()
        for item in offset_data:
            if item.data_type == 'struct':
                dep_pkg = get_msg_pkg(item.type_name, pkg_name)
                dep_msg = get_msg_type(item.type_name)
                dep_key = f"{dep_pkg}/{dep_msg}"
                if dep_key in added_imports:
                    continue
                godot_cpp_imports.append({
                    'dep_pkg': dep_pkg,
                    'msg_type': dep_msg,
                })
                added_imports.add(dep_key)

        context = {
            'container': {
                'pkg_name': pkg_name,
                'msg_type_name': msg_name,
                'offset_data': [o.to_dict() for o in offset_data],
                'base_data_size': get_base_data_size([o.to_dict() for o in offset_data]),
                'godot_cpp_imports': godot_cpp_imports,
                'get_msg_type': get_msg_type,
                'get_array_type': get_array_type,
                'get_msg_pkg': lambda name: get_msg_pkg(name, pkg_name),
                'get_godot_io_suffix': get_godot_io_suffix,
                'get_godot_cpp_array_container': get_godot_cpp_array_container,
                'is_primitive': is_primitive,
                'is_string': is_string,
                'is_array': is_array,
            }
        }
        self._generate_file(context, 'pdu_godot_conv_hpp.tpl', godot_cpp_dir, f"pdu_conv_{msg_name}.hpp", "Godot C++ converter")
