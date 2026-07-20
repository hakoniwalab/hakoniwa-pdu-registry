defmodule HakoPdu.SensorMsgs.PointCloud2Converter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_point_cloud2(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.SensorMsgs.PointCloud2.new()
    binary_read_recursive_point_cloud2(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_point_cloud2(obj) do
    {base_data, heap_data} = binary_write_recursive_point_cloud2(0, "", "", obj)
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

  def binary_read_recursive_point_cloud2(meta, binary_data, obj, base_off) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    header =
      HakoPdu.StdMsgs.HeaderConverter.binary_read_recursive_header(
        meta,
        binary_data,
        HakoPdu.StdMsgs.Header.new(),
        base_off + 0
      )

    # member: height, type: uint32 (primitive), offset: 136, size: 4
    height = read_primitive("uint32", binary_part(binary_data, base_off + 136, 4))

    # member: width, type: uint32 (primitive), offset: 140, size: 4
    width = read_primitive("uint32", binary_part(binary_data, base_off + 140, 4))

    # member: fields, type: PointField (struct), offset: 144, size: 140
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 144, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 144 + 4, 4))
    fields =
      range_indices(array_size)
      |> Enum.map(fn i ->
        HakoPdu.SensorMsgs.PointFieldConverter.binary_read_recursive_point_field(
          meta,
          binary_data,
          HakoPdu.SensorMsgs.PointField.new(),
          meta.heap_off + offset_from_heap + i * 140
        )
      end)

    # member: is_bigendian, type: bool (primitive), offset: 152, size: 4
    is_bigendian = read_primitive("bool", binary_part(binary_data, base_off + 152, 4))

    # member: point_step, type: uint32 (primitive), offset: 156, size: 4
    point_step = read_primitive("uint32", binary_part(binary_data, base_off + 156, 4))

    # member: row_step, type: uint32 (primitive), offset: 160, size: 4
    row_step = read_primitive("uint32", binary_part(binary_data, base_off + 160, 4))

    # member: data, type: uint8 (primitive), offset: 164, size: 1
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 164, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 164 + 4, 4))
    data = read_primitive_array("uint8", binary_part(binary_data, meta.heap_off + offset_from_heap, 1 * array_size), array_size, 1)

    # member: is_dense, type: bool (primitive), offset: 172, size: 4
    is_dense = read_primitive("bool", binary_part(binary_data, base_off + 172, 4))

    struct(obj, %{

      header: header,

      height: height,

      width: width,

      fields: fields,

      is_bigendian: is_bigendian,

      point_step: point_step,

      row_step: row_step,

      data: data,

      is_dense: is_dense

    })
  end

  def binary_write_recursive_point_cloud2(parent_off, heap_data, allocator, obj) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    {allocator, heap_data} =
      HakoPdu.StdMsgs.HeaderConverter.binary_write_recursive_header(
        parent_off + 0,
        heap_data,
        allocator,
        obj.header
      )

    # member: height, type: uint32 (primitive), offset: 136, size: 4
    allocator = add_binary(allocator, parent_off + 136, primitive_to_bin("uint32", obj.height, 4))

    # member: width, type: uint32 (primitive), offset: 140, size: 4
    allocator = add_binary(allocator, parent_off + 140, primitive_to_bin("uint32", obj.width, 4))

    # member: fields, type: PointField (struct), offset: 144, size: 140
    offset_from_heap = byte_size(heap_data)
    values = obj.fields || []
    allocator = add_binary(allocator, parent_off + 144, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, :binary.copy(<<0>>, length(values) * 140))
    heap_data =
      values
      |> Enum.with_index()
      |> Enum.reduce(heap_data, fn {child, i}, acc_heap ->
        {new_heap_allocator, new_heap_data} =
          HakoPdu.SensorMsgs.PointFieldConverter.binary_write_recursive_point_field(
            offset_from_heap + i * 140,
            acc_heap,
            acc_heap,
            child
          )
        add_binary(new_heap_data, 0, new_heap_allocator)
      end)

    # member: is_bigendian, type: bool (primitive), offset: 152, size: 4
    allocator = add_binary(allocator, parent_off + 152, primitive_to_bin("bool", obj.is_bigendian, 4))

    # member: point_step, type: uint32 (primitive), offset: 156, size: 4
    allocator = add_binary(allocator, parent_off + 156, primitive_to_bin("uint32", obj.point_step, 4))

    # member: row_step, type: uint32 (primitive), offset: 160, size: 4
    allocator = add_binary(allocator, parent_off + 160, primitive_to_bin("uint32", obj.row_step, 4))

    # member: data, type: uint8 (primitive), offset: 164, size: 1
    offset_from_heap = byte_size(heap_data)
    values = obj.data || []
    allocator = add_binary(allocator, parent_off + 164, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("uint8", values, 1))

    # member: is_dense, type: bool (primitive), offset: 172, size: 4
    allocator = add_binary(allocator, parent_off + 172, primitive_to_bin("bool", obj.is_dense, 4))

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
        <<value>>
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
        "char" -> string_first_byte(value)
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

  defp string_first_byte(value) do
    case to_string(value) do
      <<byte::unsigned-integer-size(8), _rest::binary>> -> <<byte>>
      _ -> <<0>>
    end
  end

  defp pad_or_trim(bytes, nil), do: bytes
  defp pad_or_trim(bytes, size) when byte_size(bytes) > size, do: binary_part(bytes, 0, size)
  defp pad_or_trim(bytes, size), do: bytes <> :binary.copy(<<0>>, size - byte_size(bytes))
end
