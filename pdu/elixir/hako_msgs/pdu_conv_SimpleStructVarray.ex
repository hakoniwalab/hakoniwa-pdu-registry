defmodule HakoPdu.HakoMsgs.SimpleStructVarrayConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_simple_struct_varray(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMsgs.SimpleStructVarray.new()
    binary_read_recursive_simple_struct_varray(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_simple_struct_varray(obj) do
    {base_data, heap_data} = binary_write_recursive_simple_struct_varray(0, "", "", obj)
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

  def binary_read_recursive_simple_struct_varray(meta, binary_data, obj, base_off) do
    # member: aaa, type: int32 (primitive), offset: 0, size: 4
    aaa = read_primitive("int32", binary_part(binary_data, base_off + 0, 4))

    # member: fixed_str, type: string (primitive), offset: 4, size: 256
    fixed_str = read_primitive_array("string", binary_part(binary_data, base_off + 4, 256), 2, div(256, 2))

    # member: varray_str, type: string (primitive), offset: 260, size: 128
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 260, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 260 + 4, 4))
    varray_str = read_primitive_array("string", binary_part(binary_data, meta.heap_off + offset_from_heap, 128 * array_size), array_size, 128)

    # member: fixed_array, type: SimpleVarray (struct), offset: 268, size: 120
    fixed_array =
      Enum.map(0..(5 - 1), fn i ->
        HakoPdu.HakoMsgs.SimpleVarrayConverter.binary_read_recursive_simple_varray(
          meta,
          binary_data,
          HakoPdu.HakoMsgs.SimpleVarray.new(),
          base_off + 268 + i * div(120, 5)
        )
      end)

    # member: data, type: SimpleVarray (struct), offset: 388, size: 24
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 388, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 388 + 4, 4))
    data =
      range_indices(array_size)
      |> Enum.map(fn i ->
        HakoPdu.HakoMsgs.SimpleVarrayConverter.binary_read_recursive_simple_varray(
          meta,
          binary_data,
          HakoPdu.HakoMsgs.SimpleVarray.new(),
          meta.heap_off + offset_from_heap + i * 24
        )
      end)

    struct(obj, %{

      aaa: aaa,

      fixed_str: fixed_str,

      varray_str: varray_str,

      fixed_array: fixed_array,

      data: data

    })
  end

  def binary_write_recursive_simple_struct_varray(parent_off, heap_data, allocator, obj) do
    # member: aaa, type: int32 (primitive), offset: 0, size: 4
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("int32", obj.aaa, 4))

    # member: fixed_str, type: string (primitive), offset: 4, size: 256
    allocator = add_binary(allocator, parent_off + 4, primitive_array_to_bin("string", obj.fixed_str, div(256, 2)))

    # member: varray_str, type: string (primitive), offset: 260, size: 128
    offset_from_heap = byte_size(heap_data)
    values = obj.varray_str || []
    allocator = add_binary(allocator, parent_off + 260, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("string", values, 128))

    # member: fixed_array, type: SimpleVarray (struct), offset: 268, size: 120
    {allocator, heap_data} =
      (obj.fixed_array || [])
      |> Enum.with_index()
      |> Enum.reduce({allocator, heap_data}, fn {child, i}, {acc_allocator, acc_heap} ->
        HakoPdu.HakoMsgs.SimpleVarrayConverter.binary_write_recursive_simple_varray(
          parent_off + 268 + i * div(120, 5),
          acc_heap,
          acc_allocator,
          child
        )
      end)

    # member: data, type: SimpleVarray (struct), offset: 388, size: 24
    offset_from_heap = byte_size(heap_data)
    values = obj.data || []
    allocator = add_binary(allocator, parent_off + 388, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, :binary.copy(<<0>>, length(values) * 24))
    heap_data =
      values
      |> Enum.with_index()
      |> Enum.reduce(heap_data, fn {child, i}, acc_heap ->
        {new_heap_allocator, new_heap_data} =
          HakoPdu.HakoMsgs.SimpleVarrayConverter.binary_write_recursive_simple_varray(
            offset_from_heap + i * 24,
            acc_heap,
            acc_heap,
            child
          )
        add_binary(new_heap_data, 0, new_heap_allocator)
      end)

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
