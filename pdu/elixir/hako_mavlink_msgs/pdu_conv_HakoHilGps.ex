defmodule HakoPdu.HakoMavlinkMsgs.HakoHilGpsConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_hako_hil_gps(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMavlinkMsgs.HakoHilGps.new()
    binary_read_recursive_hako_hil_gps(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_hako_hil_gps(obj) do
    {base_data, heap_data} = binary_write_recursive_hako_hil_gps(0, "", "", obj)
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

  def binary_read_recursive_hako_hil_gps(meta, binary_data, obj, base_off) do
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    time_usec = read_primitive("uint64", binary_part(binary_data, base_off + 0, 8))

    # member: lat, type: int32 (primitive), offset: 8, size: 4
    lat = read_primitive("int32", binary_part(binary_data, base_off + 8, 4))

    # member: lon, type: int32 (primitive), offset: 12, size: 4
    lon = read_primitive("int32", binary_part(binary_data, base_off + 12, 4))

    # member: alt, type: int32 (primitive), offset: 16, size: 4
    alt = read_primitive("int32", binary_part(binary_data, base_off + 16, 4))

    # member: eph, type: uint16 (primitive), offset: 20, size: 2
    eph = read_primitive("uint16", binary_part(binary_data, base_off + 20, 2))

    # member: epv, type: uint16 (primitive), offset: 22, size: 2
    epv = read_primitive("uint16", binary_part(binary_data, base_off + 22, 2))

    # member: vel, type: uint16 (primitive), offset: 24, size: 2
    vel = read_primitive("uint16", binary_part(binary_data, base_off + 24, 2))

    # member: vn, type: int16 (primitive), offset: 26, size: 2
    vn = read_primitive("int16", binary_part(binary_data, base_off + 26, 2))

    # member: ve, type: int16 (primitive), offset: 28, size: 2
    ve = read_primitive("int16", binary_part(binary_data, base_off + 28, 2))

    # member: vd, type: int16 (primitive), offset: 30, size: 2
    vd = read_primitive("int16", binary_part(binary_data, base_off + 30, 2))

    # member: cog, type: uint16 (primitive), offset: 32, size: 2
    cog = read_primitive("uint16", binary_part(binary_data, base_off + 32, 2))

    # member: satellites_visible, type: uint8 (primitive), offset: 34, size: 1
    satellites_visible = read_primitive("uint8", binary_part(binary_data, base_off + 34, 1))

    # member: id, type: uint8 (primitive), offset: 35, size: 1
    id = read_primitive("uint8", binary_part(binary_data, base_off + 35, 1))

    # member: yaw, type: uint8 (primitive), offset: 36, size: 1
    yaw = read_primitive("uint8", binary_part(binary_data, base_off + 36, 1))

    # member: fix_type, type: uint8 (primitive), offset: 37, size: 1
    fix_type = read_primitive("uint8", binary_part(binary_data, base_off + 37, 1))

    struct(obj, %{

      time_usec: time_usec,

      lat: lat,

      lon: lon,

      alt: alt,

      eph: eph,

      epv: epv,

      vel: vel,

      vn: vn,

      ve: ve,

      vd: vd,

      cog: cog,

      satellites_visible: satellites_visible,

      id: id,

      yaw: yaw,

      fix_type: fix_type

    })
  end

  def binary_write_recursive_hako_hil_gps(parent_off, heap_data, allocator, obj) do
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("uint64", obj.time_usec, 8))

    # member: lat, type: int32 (primitive), offset: 8, size: 4
    allocator = add_binary(allocator, parent_off + 8, primitive_to_bin("int32", obj.lat, 4))

    # member: lon, type: int32 (primitive), offset: 12, size: 4
    allocator = add_binary(allocator, parent_off + 12, primitive_to_bin("int32", obj.lon, 4))

    # member: alt, type: int32 (primitive), offset: 16, size: 4
    allocator = add_binary(allocator, parent_off + 16, primitive_to_bin("int32", obj.alt, 4))

    # member: eph, type: uint16 (primitive), offset: 20, size: 2
    allocator = add_binary(allocator, parent_off + 20, primitive_to_bin("uint16", obj.eph, 2))

    # member: epv, type: uint16 (primitive), offset: 22, size: 2
    allocator = add_binary(allocator, parent_off + 22, primitive_to_bin("uint16", obj.epv, 2))

    # member: vel, type: uint16 (primitive), offset: 24, size: 2
    allocator = add_binary(allocator, parent_off + 24, primitive_to_bin("uint16", obj.vel, 2))

    # member: vn, type: int16 (primitive), offset: 26, size: 2
    allocator = add_binary(allocator, parent_off + 26, primitive_to_bin("int16", obj.vn, 2))

    # member: ve, type: int16 (primitive), offset: 28, size: 2
    allocator = add_binary(allocator, parent_off + 28, primitive_to_bin("int16", obj.ve, 2))

    # member: vd, type: int16 (primitive), offset: 30, size: 2
    allocator = add_binary(allocator, parent_off + 30, primitive_to_bin("int16", obj.vd, 2))

    # member: cog, type: uint16 (primitive), offset: 32, size: 2
    allocator = add_binary(allocator, parent_off + 32, primitive_to_bin("uint16", obj.cog, 2))

    # member: satellites_visible, type: uint8 (primitive), offset: 34, size: 1
    allocator = add_binary(allocator, parent_off + 34, primitive_to_bin("uint8", obj.satellites_visible, 1))

    # member: id, type: uint8 (primitive), offset: 35, size: 1
    allocator = add_binary(allocator, parent_off + 35, primitive_to_bin("uint8", obj.id, 1))

    # member: yaw, type: uint8 (primitive), offset: 36, size: 1
    allocator = add_binary(allocator, parent_off + 36, primitive_to_bin("uint8", obj.yaw, 1))

    # member: fix_type, type: uint8 (primitive), offset: 37, size: 1
    allocator = add_binary(allocator, parent_off + 37, primitive_to_bin("uint8", obj.fix_type, 1))

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
