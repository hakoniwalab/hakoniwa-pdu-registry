defmodule {{ container.converter_module_name }} do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_{{ container.func_name }}(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = {{ container.module_name }}.new()
    binary_read_recursive_{{ container.func_name }}(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_{{ container.func_name }}(obj) do
    {base_data, heap_data} = binary_write_recursive_{{ container.func_name }}(0, "", "", obj)
    heap_off = @pdu_meta_data_size + byte_size(base_data)
    total_size = heap_off + byte_size(heap_data)
    metadata = <<
      @pdu_meta_data_magicno::little-unsigned-integer-size(32),
      @pdu_meta_data_version::little-unsigned-integer-size(32),
      @pdu_meta_data_size::little-unsigned-integer-size(32),
      heap_off::little-unsigned-integer-size(32),
      total_size::little-unsigned-integer-size(32),
      0::little-unsigned-integer-size(32)
    >>
    metadata <> base_data <> heap_data
  end

  def binary_read_recursive_{{ container.func_name }}(meta, binary_data, obj, base_off) do
{%- for item in container.offset_data %}
    # member: {{ item.member_name }}, type: {{ item.type_name }} ({{ item.data_type }}), offset: {{ item.offset }}, size: {{ item.size }}
{%- if item.data_type == 'primitive' or item.data_type == 'string' %}
{%- if item.array_type == 'single' %}
    {{ item.member_name }} = read_primitive("{{ item.type_name }}", binary_part(binary_data, base_off + {{ item.offset }}, {{ item.size }}))
{%- elif item.array_type == 'array' %}
    {{ item.member_name }} = read_primitive_array("{{ container.get_array_type(item.type_name) }}", binary_part(binary_data, base_off + {{ item.offset }}, {{ item.size }}), {{ item.array_len }}, div({{ item.size }}, {{ item.array_len }}))
{%- else %}
    array_size = read_primitive("int32", binary_part(binary_data, base_off + {{ item.offset }}, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + {{ item.offset }} + 4, 4))
    {{ item.member_name }} = read_primitive_array("{{ item.type_name }}", binary_part(binary_data, meta.heap_off + offset_from_heap, {{ item.size }} * array_size), array_size, {{ item.size }})
{%- endif %}
{%- else %}
{%- if item.array_type == 'single' %}
    {{ item.member_name }} =
      {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
        meta,
        binary_data,
        {{ container.get_elixir_type_ref(item.type_name) }}.new(),
        base_off + {{ item.offset }}
      )
{%- elif item.array_type == 'array' %}
    {{ item.member_name }} =
      Enum.map(0..({{ item.array_len }} - 1), fn i ->
        {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
          meta,
          binary_data,
          {{ container.get_elixir_type_ref(item.type_name) }}.new(),
          base_off + {{ item.offset }} + i * div({{ item.size }}, {{ item.array_len }})
        )
      end)
{%- else %}
    array_size = read_primitive("int32", binary_part(binary_data, base_off + {{ item.offset }}, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + {{ item.offset }} + 4, 4))
    {{ item.member_name }} =
      range_indices(array_size)
      |> Enum.map(fn i ->
        {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
          meta,
          binary_data,
          {{ container.get_elixir_type_ref(item.type_name) }}.new(),
          meta.heap_off + offset_from_heap + i * {{ item.size }}
        )
      end)
{%- endif %}
{%- endif %}
{% endfor %}
    struct(obj, %{
{% for item in container.offset_data %}
      {{ item.member_name }}: {{ item.member_name }}{% if not loop.last %},{% endif %}
{% endfor %}
    })
  end

  def binary_write_recursive_{{ container.func_name }}(parent_off, heap_data, allocator, obj) do
{%- for item in container.offset_data %}
    # member: {{ item.member_name }}, type: {{ item.type_name }} ({{ item.data_type }}), offset: {{ item.offset }}, size: {{ item.size }}
{%- if item.data_type == 'primitive' or item.data_type == 'string' %}
{%- if item.array_type == 'single' %}
    allocator = add_binary(allocator, parent_off + {{ item.offset }}, primitive_to_bin("{{ item.type_name }}", obj.{{ item.member_name }}, {{ item.size }}))
{%- elif item.array_type == 'array' %}
    allocator = add_binary(allocator, parent_off + {{ item.offset }}, primitive_array_to_bin("{{ container.get_array_type(item.type_name) }}", obj.{{ item.member_name }}, div({{ item.size }}, {{ item.array_len }})))
{%- else %}
    offset_from_heap = byte_size(heap_data)
    values = obj.{{ item.member_name }} || []
    allocator = add_binary(allocator, parent_off + {{ item.offset }}, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("{{ item.type_name }}", values, {{ item.size }}))
{%- endif %}
{%- else %}
{%- if item.array_type == 'single' %}
    {allocator, heap_data} =
      {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
        parent_off + {{ item.offset }},
        heap_data,
        allocator,
        obj.{{ item.member_name }}
      )
{%- elif item.array_type == 'array' %}
    {allocator, heap_data} =
      (obj.{{ item.member_name }} || [])
      |> Enum.with_index()
      |> Enum.reduce({allocator, heap_data}, fn {child, i}, {acc_allocator, acc_heap} ->
        {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
          parent_off + {{ item.offset }} + i * div({{ item.size }}, {{ item.array_len }}),
          acc_heap,
          acc_allocator,
          child
        )
      end)
{%- else %}
    offset_from_heap = byte_size(heap_data)
    values = obj.{{ item.member_name }} || []
    allocator = add_binary(allocator, parent_off + {{ item.offset }}, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, :binary.copy(<<0>>, length(values) * {{ item.size }}))
    heap_data =
      values
      |> Enum.with_index()
      |> Enum.reduce(heap_data, fn {child, i}, acc_heap ->
        {new_heap_allocator, new_heap_data} =
          {{ container.get_elixir_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(
            offset_from_heap + i * {{ item.size }},
            acc_heap,
            acc_heap,
            child
          )
        add_binary(new_heap_data, 0, new_heap_allocator)
      end)
{%- endif %}
{%- endif %}
{% endfor %}
    {allocator, heap_data}
  end

  def load_pdu_meta(binary_data) when is_binary(binary_data) do
    if byte_size(binary_data) < @pdu_meta_data_size do
      raise ArgumentError, "PDU is too small for metadata"
    end

    <<
      magic::little-unsigned-integer-size(32),
      version::little-unsigned-integer-size(32),
      base_off::little-unsigned-integer-size(32),
      heap_off::little-unsigned-integer-size(32),
      total_size::little-unsigned-integer-size(32),
      _reserved::little-unsigned-integer-size(32),
      _rest::binary
    >> = binary_data

    if magic != @pdu_meta_data_magicno or version != @pdu_meta_data_version do
      raise ArgumentError, "Invalid PDU metadata"
    end

    %{magic: magic, version: version, base_off: base_off, heap_off: heap_off, total_size: total_size}
  end

  defp add_binary(buffer, offset, data) do
    buffer = if byte_size(buffer) < offset do
      buffer <> :binary.copy(<<0>>, offset - byte_size(buffer))
    else
      buffer
    end

    end_offset = offset + byte_size(data)
    buffer = if byte_size(buffer) < end_offset do
      buffer <> :binary.copy(<<0>>, end_offset - byte_size(buffer))
    else
      buffer
    end

    prefix = binary_part(buffer, 0, offset)
    suffix_offset = offset + byte_size(data)
    suffix_size = byte_size(buffer) - suffix_offset
    suffix = if suffix_size > 0, do: binary_part(buffer, suffix_offset, suffix_size), else: ""
    prefix <> data <> suffix
  end

  defp read_primitive(type, bytes) do
    case type do
      "bool" ->
        <<value::little-unsigned-integer-size(32)>> = bytes
        value != 0
      "byte" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "uint8" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "char" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "int8" ->
        <<value::signed-integer-size(8)>> = bytes
        value
      "int16" ->
        <<value::little-signed-integer-size(16)>> = bytes
        value
      "uint16" ->
        <<value::little-unsigned-integer-size(16)>> = bytes
        value
      "int32" ->
        <<value::little-signed-integer-size(32)>> = bytes
        value
      "uint32" ->
        <<value::little-unsigned-integer-size(32)>> = bytes
        value
      "int64" ->
        <<value::little-signed-integer-size(64)>> = bytes
        value
      "uint64" ->
        <<value::little-unsigned-integer-size(64)>> = bytes
        value
      "float32" ->
        <<value::little-float-size(32)>> = bytes
        value
      "float64" ->
        <<value::little-float-size(64)>> = bytes
        value
      "string" ->
        bytes |> :binary.split(<<0>>) |> List.first()
      _ ->
        raise ArgumentError, "Unsupported primitive type: #{type}"
    end
  end

  defp primitive_to_bin(type, value, size \\ nil) do
    bytes =
      case type do
        "bool" -> <<if(value, do: 1, else: 0)::little-unsigned-integer-size(32)>>
        "byte" -> <<value::unsigned-integer-size(8)>>
        "uint8" -> <<value::unsigned-integer-size(8)>>
        "char" -> <<value::unsigned-integer-size(8)>>
        "int8" -> <<value::signed-integer-size(8)>>
        "int16" -> <<value::little-signed-integer-size(16)>>
        "uint16" -> <<value::little-unsigned-integer-size(16)>>
        "int32" -> <<value::little-signed-integer-size(32)>>
        "uint32" -> <<value::little-unsigned-integer-size(32)>>
        "int64" -> <<value::little-signed-integer-size(64)>>
        "uint64" -> <<value::little-unsigned-integer-size(64)>>
        "float32" -> <<value::little-float-size(32)>>
        "float64" -> <<value::little-float-size(64)>>
        "string" -> to_string(value) <> <<0>>
        _ -> raise ArgumentError, "Unsupported primitive type: #{type}"
      end

    pad_or_trim(bytes, size)
  end

  defp read_primitive_array(_type, _bytes, 0, _element_size), do: []
  defp read_primitive_array(type, bytes, count, element_size) do
    count
    |> range_indices()
    |> Enum.map(fn i ->
      read_primitive(type, binary_part(bytes, i * element_size, element_size))
    end)
  end

  defp primitive_array_to_bin(type, values, element_size \\ nil) do
    (values || [])
    |> Enum.map_join("", &primitive_to_bin(type, &1, element_size))
  end

  defp range_indices(count) when count <= 0, do: []
  defp range_indices(count), do: 0..(count - 1)

  defp pad_or_trim(bytes, nil), do: bytes
  defp pad_or_trim(bytes, size) when byte_size(bytes) > size, do: binary_part(bytes, 0, size)
  defp pad_or_trim(bytes, size), do: bytes <> :binary.copy(<<0>>, size - byte_size(bytes))
end
