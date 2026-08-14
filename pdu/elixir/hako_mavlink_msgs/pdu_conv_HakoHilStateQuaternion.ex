defmodule HakoPdu.HakoMavlinkMsgs.HakoHilStateQuaternionConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_hako_hil_state_quaternion(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMavlinkMsgs.HakoHilStateQuaternion.new()
    binary_read_recursive_hako_hil_state_quaternion(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_hako_hil_state_quaternion(obj) do
    {base_data, heap_data} = binary_write_recursive_hako_hil_state_quaternion(0, "", "", obj)
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

  def binary_read_recursive_hako_hil_state_quaternion(meta, binary_data, obj, base_off) do
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    time_usec = read_primitive("uint64", binary_part(binary_data, base_off + 0, 8))

    # member: attitude_quaternion, type: float32 (primitive), offset: 8, size: 16
    attitude_quaternion = read_primitive_array("float32", binary_part(binary_data, base_off + 8, 16), 4, div(16, 4))

    # member: rollspeed, type: float32 (primitive), offset: 24, size: 4
    rollspeed = read_primitive("float32", binary_part(binary_data, base_off + 24, 4))

    # member: pitchspeed, type: float32 (primitive), offset: 28, size: 4
    pitchspeed = read_primitive("float32", binary_part(binary_data, base_off + 28, 4))

    # member: yawspeed, type: float32 (primitive), offset: 32, size: 4
    yawspeed = read_primitive("float32", binary_part(binary_data, base_off + 32, 4))

    # member: lat, type: int32 (primitive), offset: 36, size: 4
    lat = read_primitive("int32", binary_part(binary_data, base_off + 36, 4))

    # member: lon, type: int32 (primitive), offset: 40, size: 4
    lon = read_primitive("int32", binary_part(binary_data, base_off + 40, 4))

    # member: alt, type: int32 (primitive), offset: 44, size: 4
    alt = read_primitive("int32", binary_part(binary_data, base_off + 44, 4))

    # member: vx, type: int16 (primitive), offset: 48, size: 2
    vx = read_primitive("int16", binary_part(binary_data, base_off + 48, 2))

    # member: vy, type: int16 (primitive), offset: 50, size: 2
    vy = read_primitive("int16", binary_part(binary_data, base_off + 50, 2))

    # member: vz, type: int16 (primitive), offset: 52, size: 2
    vz = read_primitive("int16", binary_part(binary_data, base_off + 52, 2))

    # member: ind_airspeed, type: uint16 (primitive), offset: 54, size: 2
    ind_airspeed = read_primitive("uint16", binary_part(binary_data, base_off + 54, 2))

    # member: true_airspeed, type: uint16 (primitive), offset: 56, size: 2
    true_airspeed = read_primitive("uint16", binary_part(binary_data, base_off + 56, 2))

    # member: xacc, type: int16 (primitive), offset: 58, size: 2
    xacc = read_primitive("int16", binary_part(binary_data, base_off + 58, 2))

    # member: yacc, type: int16 (primitive), offset: 60, size: 2
    yacc = read_primitive("int16", binary_part(binary_data, base_off + 60, 2))

    # member: zacc, type: int16 (primitive), offset: 62, size: 2
    zacc = read_primitive("int16", binary_part(binary_data, base_off + 62, 2))

    struct(obj, %{

      time_usec: time_usec,

      attitude_quaternion: attitude_quaternion,

      rollspeed: rollspeed,

      pitchspeed: pitchspeed,

      yawspeed: yawspeed,

      lat: lat,

      lon: lon,

      alt: alt,

      vx: vx,

      vy: vy,

      vz: vz,

      ind_airspeed: ind_airspeed,

      true_airspeed: true_airspeed,

      xacc: xacc,

      yacc: yacc,

      zacc: zacc

    })
  end

  def binary_write_recursive_hako_hil_state_quaternion(parent_off, heap_data, allocator, obj) do
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("uint64", obj.time_usec, 8))

    # member: attitude_quaternion, type: float32 (primitive), offset: 8, size: 16
    allocator = add_binary(allocator, parent_off + 8, primitive_array_to_bin("float32", obj.attitude_quaternion, div(16, 4)))

    # member: rollspeed, type: float32 (primitive), offset: 24, size: 4
    allocator = add_binary(allocator, parent_off + 24, primitive_to_bin("float32", obj.rollspeed, 4))

    # member: pitchspeed, type: float32 (primitive), offset: 28, size: 4
    allocator = add_binary(allocator, parent_off + 28, primitive_to_bin("float32", obj.pitchspeed, 4))

    # member: yawspeed, type: float32 (primitive), offset: 32, size: 4
    allocator = add_binary(allocator, parent_off + 32, primitive_to_bin("float32", obj.yawspeed, 4))

    # member: lat, type: int32 (primitive), offset: 36, size: 4
    allocator = add_binary(allocator, parent_off + 36, primitive_to_bin("int32", obj.lat, 4))

    # member: lon, type: int32 (primitive), offset: 40, size: 4
    allocator = add_binary(allocator, parent_off + 40, primitive_to_bin("int32", obj.lon, 4))

    # member: alt, type: int32 (primitive), offset: 44, size: 4
    allocator = add_binary(allocator, parent_off + 44, primitive_to_bin("int32", obj.alt, 4))

    # member: vx, type: int16 (primitive), offset: 48, size: 2
    allocator = add_binary(allocator, parent_off + 48, primitive_to_bin("int16", obj.vx, 2))

    # member: vy, type: int16 (primitive), offset: 50, size: 2
    allocator = add_binary(allocator, parent_off + 50, primitive_to_bin("int16", obj.vy, 2))

    # member: vz, type: int16 (primitive), offset: 52, size: 2
    allocator = add_binary(allocator, parent_off + 52, primitive_to_bin("int16", obj.vz, 2))

    # member: ind_airspeed, type: uint16 (primitive), offset: 54, size: 2
    allocator = add_binary(allocator, parent_off + 54, primitive_to_bin("uint16", obj.ind_airspeed, 2))

    # member: true_airspeed, type: uint16 (primitive), offset: 56, size: 2
    allocator = add_binary(allocator, parent_off + 56, primitive_to_bin("uint16", obj.true_airspeed, 2))

    # member: xacc, type: int16 (primitive), offset: 58, size: 2
    allocator = add_binary(allocator, parent_off + 58, primitive_to_bin("int16", obj.xacc, 2))

    # member: yacc, type: int16 (primitive), offset: 60, size: 2
    allocator = add_binary(allocator, parent_off + 60, primitive_to_bin("int16", obj.yacc, 2))

    # member: zacc, type: int16 (primitive), offset: 62, size: 2
    allocator = add_binary(allocator, parent_off + 62, primitive_to_bin("int16", obj.zacc, 2))

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
