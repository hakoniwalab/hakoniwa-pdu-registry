defmodule HakoPdu.HakoMsgs.MetaPduConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_meta_pdu(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMsgs.MetaPdu.new()
    binary_read_recursive_meta_pdu(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_meta_pdu(obj) do
    {base_data, heap_data} = binary_write_recursive_meta_pdu(0, "", "", obj)
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

  def binary_read_recursive_meta_pdu(meta, binary_data, obj, base_off) do
    # member: total_len, type: uint32 (primitive), offset: 0, size: 4
    total_len = read_primitive("uint32", binary_part(binary_data, base_off + 0, 4))

    # member: magicno, type: uint32 (primitive), offset: 4, size: 4
    magicno = read_primitive("uint32", binary_part(binary_data, base_off + 4, 4))

    # member: version, type: uint16 (primitive), offset: 8, size: 2
    version = read_primitive("uint16", binary_part(binary_data, base_off + 8, 2))

    # member: flags, type: uint16 (primitive), offset: 10, size: 2
    flags = read_primitive("uint16", binary_part(binary_data, base_off + 10, 2))

    # member: meta_request_type, type: uint32 (primitive), offset: 12, size: 4
    meta_request_type = read_primitive("uint32", binary_part(binary_data, base_off + 12, 4))

    # member: hako_time_us, type: uint64 (primitive), offset: 16, size: 8
    hako_time_us = read_primitive("uint64", binary_part(binary_data, base_off + 16, 8))

    # member: asset_time_us, type: uint64 (primitive), offset: 24, size: 8
    asset_time_us = read_primitive("uint64", binary_part(binary_data, base_off + 24, 8))

    # member: real_time_us, type: uint64 (primitive), offset: 32, size: 8
    real_time_us = read_primitive("uint64", binary_part(binary_data, base_off + 32, 8))

    # member: robot_name, type: string (primitive), offset: 40, size: 128
    robot_name = read_primitive("string", binary_part(binary_data, base_off + 40, 128))

    # member: channel_id, type: int32 (primitive), offset: 168, size: 4
    channel_id = read_primitive("int32", binary_part(binary_data, base_off + 168, 4))

    # member: body_len, type: uint32 (primitive), offset: 172, size: 4
    body_len = read_primitive("uint32", binary_part(binary_data, base_off + 172, 4))

    struct(obj, %{

      total_len: total_len,

      magicno: magicno,

      version: version,

      flags: flags,

      meta_request_type: meta_request_type,

      hako_time_us: hako_time_us,

      asset_time_us: asset_time_us,

      real_time_us: real_time_us,

      robot_name: robot_name,

      channel_id: channel_id,

      body_len: body_len

    })
  end

  def binary_write_recursive_meta_pdu(parent_off, heap_data, allocator, obj) do
    # member: total_len, type: uint32 (primitive), offset: 0, size: 4
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("uint32", obj.total_len, 4))

    # member: magicno, type: uint32 (primitive), offset: 4, size: 4
    allocator = add_binary(allocator, parent_off + 4, primitive_to_bin("uint32", obj.magicno, 4))

    # member: version, type: uint16 (primitive), offset: 8, size: 2
    allocator = add_binary(allocator, parent_off + 8, primitive_to_bin("uint16", obj.version, 2))

    # member: flags, type: uint16 (primitive), offset: 10, size: 2
    allocator = add_binary(allocator, parent_off + 10, primitive_to_bin("uint16", obj.flags, 2))

    # member: meta_request_type, type: uint32 (primitive), offset: 12, size: 4
    allocator = add_binary(allocator, parent_off + 12, primitive_to_bin("uint32", obj.meta_request_type, 4))

    # member: hako_time_us, type: uint64 (primitive), offset: 16, size: 8
    allocator = add_binary(allocator, parent_off + 16, primitive_to_bin("uint64", obj.hako_time_us, 8))

    # member: asset_time_us, type: uint64 (primitive), offset: 24, size: 8
    allocator = add_binary(allocator, parent_off + 24, primitive_to_bin("uint64", obj.asset_time_us, 8))

    # member: real_time_us, type: uint64 (primitive), offset: 32, size: 8
    allocator = add_binary(allocator, parent_off + 32, primitive_to_bin("uint64", obj.real_time_us, 8))

    # member: robot_name, type: string (primitive), offset: 40, size: 128
    allocator = add_binary(allocator, parent_off + 40, primitive_to_bin("string", obj.robot_name, 128))

    # member: channel_id, type: int32 (primitive), offset: 168, size: 4
    allocator = add_binary(allocator, parent_off + 168, primitive_to_bin("int32", obj.channel_id, 4))

    # member: body_len, type: uint32 (primitive), offset: 172, size: 4
    allocator = add_binary(allocator, parent_off + 172, primitive_to_bin("uint32", obj.body_len, 4))

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
