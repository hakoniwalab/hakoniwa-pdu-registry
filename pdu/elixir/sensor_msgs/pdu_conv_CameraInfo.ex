defmodule HakoPdu.SensorMsgs.CameraInfoConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_camera_info(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.SensorMsgs.CameraInfo.new()
    binary_read_recursive_camera_info(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_camera_info(obj) do
    {base_data, heap_data} = binary_write_recursive_camera_info(0, "", "", obj)
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

  def binary_read_recursive_camera_info(meta, binary_data, obj, base_off) do
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

    # member: distortion_model, type: string (primitive), offset: 144, size: 128
    distortion_model = read_primitive("string", binary_part(binary_data, base_off + 144, 128))

    # member: d, type: float64 (primitive), offset: 272, size: 8
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 272, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 272 + 4, 4))
    d = read_primitive_array("float64", binary_part(binary_data, meta.heap_off + offset_from_heap, 8 * array_size), array_size, 8)

    # member: k, type: float64 (primitive), offset: 280, size: 72
    k = read_primitive_array("float64", binary_part(binary_data, base_off + 280, 72), 9, div(72, 9))

    # member: r, type: float64 (primitive), offset: 352, size: 72
    r = read_primitive_array("float64", binary_part(binary_data, base_off + 352, 72), 9, div(72, 9))

    # member: p, type: float64 (primitive), offset: 424, size: 96
    p = read_primitive_array("float64", binary_part(binary_data, base_off + 424, 96), 12, div(96, 12))

    # member: binning_x, type: uint32 (primitive), offset: 520, size: 4
    binning_x = read_primitive("uint32", binary_part(binary_data, base_off + 520, 4))

    # member: binning_y, type: uint32 (primitive), offset: 524, size: 4
    binning_y = read_primitive("uint32", binary_part(binary_data, base_off + 524, 4))

    # member: roi, type: RegionOfInterest (struct), offset: 528, size: 20
    roi =
      HakoPdu.SensorMsgs.RegionOfInterestConverter.binary_read_recursive_region_of_interest(
        meta,
        binary_data,
        HakoPdu.SensorMsgs.RegionOfInterest.new(),
        base_off + 528
      )

    struct(obj, %{

      header: header,

      height: height,

      width: width,

      distortion_model: distortion_model,

      d: d,

      k: k,

      r: r,

      p: p,

      binning_x: binning_x,

      binning_y: binning_y,

      roi: roi

    })
  end

  def binary_write_recursive_camera_info(parent_off, heap_data, allocator, obj) do
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

    # member: distortion_model, type: string (primitive), offset: 144, size: 128
    allocator = add_binary(allocator, parent_off + 144, primitive_to_bin("string", obj.distortion_model, 128))

    # member: d, type: float64 (primitive), offset: 272, size: 8
    offset_from_heap = byte_size(heap_data)
    values = obj.d || []
    allocator = add_binary(allocator, parent_off + 272, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("float64", values, 8))

    # member: k, type: float64 (primitive), offset: 280, size: 72
    allocator = add_binary(allocator, parent_off + 280, primitive_array_to_bin("float64", obj.k, div(72, 9)))

    # member: r, type: float64 (primitive), offset: 352, size: 72
    allocator = add_binary(allocator, parent_off + 352, primitive_array_to_bin("float64", obj.r, div(72, 9)))

    # member: p, type: float64 (primitive), offset: 424, size: 96
    allocator = add_binary(allocator, parent_off + 424, primitive_array_to_bin("float64", obj.p, div(96, 12)))

    # member: binning_x, type: uint32 (primitive), offset: 520, size: 4
    allocator = add_binary(allocator, parent_off + 520, primitive_to_bin("uint32", obj.binning_x, 4))

    # member: binning_y, type: uint32 (primitive), offset: 524, size: 4
    allocator = add_binary(allocator, parent_off + 524, primitive_to_bin("uint32", obj.binning_y, 4))

    # member: roi, type: RegionOfInterest (struct), offset: 528, size: 20
    {allocator, heap_data} =
      HakoPdu.SensorMsgs.RegionOfInterestConverter.binary_write_recursive_region_of_interest(
        parent_off + 528,
        heap_data,
        allocator,
        obj.roi
      )

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
