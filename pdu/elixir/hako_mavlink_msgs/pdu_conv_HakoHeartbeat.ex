defmodule HakoPdu.HakoMavlinkMsgs.HakoHeartbeatConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_hako_heartbeat(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMavlinkMsgs.HakoHeartbeat.new()
    binary_read_recursive_hako_heartbeat(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_hako_heartbeat(obj) do
    {base_data, heap_data} = binary_write_recursive_hako_heartbeat(0, "", "", obj)
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

  def binary_read_recursive_hako_heartbeat(meta, binary_data, obj, base_off) do
    # member: type, type: uint8 (primitive), offset: 0, size: 1
    type = read_primitive("uint8", binary_part(binary_data, base_off + 0, 1))

    # member: autopilot, type: uint8 (primitive), offset: 1, size: 1
    autopilot = read_primitive("uint8", binary_part(binary_data, base_off + 1, 1))

    # member: base_mode, type: uint8 (primitive), offset: 2, size: 1
    base_mode = read_primitive("uint8", binary_part(binary_data, base_off + 2, 1))

    # member: custom_mode, type: uint32 (primitive), offset: 4, size: 4
    custom_mode = read_primitive("uint32", binary_part(binary_data, base_off + 4, 4))

    # member: system_status, type: uint8 (primitive), offset: 8, size: 1
    system_status = read_primitive("uint8", binary_part(binary_data, base_off + 8, 1))

    # member: mavlink_version, type: uint8 (primitive), offset: 9, size: 1
    mavlink_version = read_primitive("uint8", binary_part(binary_data, base_off + 9, 1))

    struct(obj, %{

      type: type,

      autopilot: autopilot,

      base_mode: base_mode,

      custom_mode: custom_mode,

      system_status: system_status,

      mavlink_version: mavlink_version

    })
  end

  def binary_write_recursive_hako_heartbeat(parent_off, heap_data, allocator, obj) do
    # member: type, type: uint8 (primitive), offset: 0, size: 1
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("uint8", obj.type, 1))

    # member: autopilot, type: uint8 (primitive), offset: 1, size: 1
    allocator = add_binary(allocator, parent_off + 1, primitive_to_bin("uint8", obj.autopilot, 1))

    # member: base_mode, type: uint8 (primitive), offset: 2, size: 1
    allocator = add_binary(allocator, parent_off + 2, primitive_to_bin("uint8", obj.base_mode, 1))

    # member: custom_mode, type: uint32 (primitive), offset: 4, size: 4
    allocator = add_binary(allocator, parent_off + 4, primitive_to_bin("uint32", obj.custom_mode, 4))

    # member: system_status, type: uint8 (primitive), offset: 8, size: 1
    allocator = add_binary(allocator, parent_off + 8, primitive_to_bin("uint8", obj.system_status, 1))

    # member: mavlink_version, type: uint8 (primitive), offset: 9, size: 1
    allocator = add_binary(allocator, parent_off + 9, primitive_to_bin("uint8", obj.mavlink_version, 1))

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
