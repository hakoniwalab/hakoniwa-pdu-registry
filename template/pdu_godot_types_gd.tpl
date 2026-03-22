class_name {{ container.godot_global_class_name }}
extends RefCounted

{% for item in container.godot_imports %}
{% if item.dep_pkg == container.pkg_name %}const {{ item.class_name }}Script = preload("./{{ item.class_name }}.gd")
{% else %}const {{ item.class_name }}Script = preload("../{{ item.dep_pkg }}/{{ item.class_name }}.gd")
{% endif %}
{% endfor %}
{%- for field in container.json_data["fields"] %}
var {{ field.name }}: {{ container.get_godot_type_hint_with_pkg(field.type) }} = {{ container.get_godot_default_value_with_pkg(field.type) }}
{%- endfor %}

static func from_dict(d: Dictionary) -> {{ container.godot_global_class_name }}:
    var obj := {{ container.godot_global_class_name }}.new()
{%- for field in container.json_data["fields"] %}
    if d.has("{{ field.name }}"):
    {%- if container.is_array(field.type) %}
        {%- set array_type = container.get_array_type(field.type) %}
        {%- if container.is_primitive(array_type) or container.is_string(array_type) %}
        obj.{{ field.name }} = d["{{ field.name }}"]
        {%- else %}
        obj.{{ field.name }} = []
        for item in d["{{ field.name }}"]:
            obj.{{ field.name }}.append({{ container.get_godot_class_name(array_type) }}Script.from_dict(item))
        {%- endif %}
    {%- elif container.is_primitive(field.type) or container.is_string(field.type) %}
        obj.{{ field.name }} = d["{{ field.name }}"]
    {%- else %}
        obj.{{ field.name }} = {{ container.get_godot_class_name(field.type) }}Script.from_dict(d["{{ field.name }}"])
    {%- endif %}
{%- endfor %}
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
{%- for field in container.json_data["fields"] %}
    {%- if container.is_array(field.type) %}
        {%- set array_type = container.get_array_type(field.type) %}
        {%- if container.is_primitive(array_type) or container.is_string(array_type) %}
    d["{{ field.name }}"] = {{ field.name }}
        {%- else %}
    var {{ field.name }}_array: Array = []
    for item in {{ field.name }}:
        {{ field.name }}_array.append(item.to_dict())
    d["{{ field.name }}"] = {{ field.name }}_array
        {%- endif %}
    {%- elif container.is_primitive(field.type) or container.is_string(field.type) %}
    d["{{ field.name }}"] = {{ field.name }}
    {%- else %}
    d["{{ field.name }}"] = {{ field.name }}.to_dict()
    {%- endif %}
{%- endfor %}
    return d
