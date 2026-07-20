defmodule HakoPdu.HakoMavlink2Msgs.HakoSERVO_OUTPUT_RAWConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMavlink2Msgs.HakoSERVO_OUTPUT_RAW.new()
    binary_read_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(obj) do
    {base_data, heap_data} = binary_write_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(0, "", "", obj)
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

  def binary_read_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(meta, binary_data, obj, base_off) do
    # member: time_usec, type: uint32 (primitive), offset: 0, size: 4
    time_usec = read_primitive("uint32", binary_part(binary_data, base_off + 0, 4))

    # member: port, type: uint8 (primitive), offset: 4, size: 1
    port = read_primitive("uint8", binary_part(binary_data, base_off + 4, 1))

    # member: servo1_raw, type: uint16 (primitive), offset: 6, size: 2
    servo1_raw = read_primitive("uint16", binary_part(binary_data, base_off + 6, 2))

    # member: servo2_raw, type: uint16 (primitive), offset: 8, size: 2
    servo2_raw = read_primitive("uint16", binary_part(binary_data, base_off + 8, 2))

    # member: servo3_raw, type: uint16 (primitive), offset: 10, size: 2
    servo3_raw = read_primitive("uint16", binary_part(binary_data, base_off + 10, 2))

    # member: servo4_raw, type: uint16 (primitive), offset: 12, size: 2
    servo4_raw = read_primitive("uint16", binary_part(binary_data, base_off + 12, 2))

    # member: servo5_raw, type: uint16 (primitive), offset: 14, size: 2
    servo5_raw = read_primitive("uint16", binary_part(binary_data, base_off + 14, 2))

    # member: servo6_raw, type: uint16 (primitive), offset: 16, size: 2
    servo6_raw = read_primitive("uint16", binary_part(binary_data, base_off + 16, 2))

    # member: servo7_raw, type: uint16 (primitive), offset: 18, size: 2
    servo7_raw = read_primitive("uint16", binary_part(binary_data, base_off + 18, 2))

    # member: servo8_raw, type: uint16 (primitive), offset: 20, size: 2
    servo8_raw = read_primitive("uint16", binary_part(binary_data, base_off + 20, 2))

    # member: servo9_raw, type: uint16 (primitive), offset: 22, size: 2
    servo9_raw = read_primitive("uint16", binary_part(binary_data, base_off + 22, 2))

    # member: servo10_raw, type: uint16 (primitive), offset: 24, size: 2
    servo10_raw = read_primitive("uint16", binary_part(binary_data, base_off + 24, 2))

    # member: servo11_raw, type: uint16 (primitive), offset: 26, size: 2
    servo11_raw = read_primitive("uint16", binary_part(binary_data, base_off + 26, 2))

    # member: servo12_raw, type: uint16 (primitive), offset: 28, size: 2
    servo12_raw = read_primitive("uint16", binary_part(binary_data, base_off + 28, 2))

    # member: servo13_raw, type: uint16 (primitive), offset: 30, size: 2
    servo13_raw = read_primitive("uint16", binary_part(binary_data, base_off + 30, 2))

    # member: servo14_raw, type: uint16 (primitive), offset: 32, size: 2
    servo14_raw = read_primitive("uint16", binary_part(binary_data, base_off + 32, 2))

    # member: servo15_raw, type: uint16 (primitive), offset: 34, size: 2
    servo15_raw = read_primitive("uint16", binary_part(binary_data, base_off + 34, 2))

    # member: servo16_raw, type: uint16 (primitive), offset: 36, size: 2
    servo16_raw = read_primitive("uint16", binary_part(binary_data, base_off + 36, 2))

    struct(obj, %{

      time_usec: time_usec,

      port: port,

      servo1_raw: servo1_raw,

      servo2_raw: servo2_raw,

      servo3_raw: servo3_raw,

      servo4_raw: servo4_raw,

      servo5_raw: servo5_raw,

      servo6_raw: servo6_raw,

      servo7_raw: servo7_raw,

      servo8_raw: servo8_raw,

      servo9_raw: servo9_raw,

      servo10_raw: servo10_raw,

      servo11_raw: servo11_raw,

      servo12_raw: servo12_raw,

      servo13_raw: servo13_raw,

      servo14_raw: servo14_raw,

      servo15_raw: servo15_raw,

      servo16_raw: servo16_raw

    })
  end

  def binary_write_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(parent_off, heap_data, allocator, obj) do
    # member: time_usec, type: uint32 (primitive), offset: 0, size: 4
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("uint32", obj.time_usec, 4))

    # member: port, type: uint8 (primitive), offset: 4, size: 1
    allocator = add_binary(allocator, parent_off + 4, primitive_to_bin("uint8", obj.port, 1))

    # member: servo1_raw, type: uint16 (primitive), offset: 6, size: 2
    allocator = add_binary(allocator, parent_off + 6, primitive_to_bin("uint16", obj.servo1_raw, 2))

    # member: servo2_raw, type: uint16 (primitive), offset: 8, size: 2
    allocator = add_binary(allocator, parent_off + 8, primitive_to_bin("uint16", obj.servo2_raw, 2))

    # member: servo3_raw, type: uint16 (primitive), offset: 10, size: 2
    allocator = add_binary(allocator, parent_off + 10, primitive_to_bin("uint16", obj.servo3_raw, 2))

    # member: servo4_raw, type: uint16 (primitive), offset: 12, size: 2
    allocator = add_binary(allocator, parent_off + 12, primitive_to_bin("uint16", obj.servo4_raw, 2))

    # member: servo5_raw, type: uint16 (primitive), offset: 14, size: 2
    allocator = add_binary(allocator, parent_off + 14, primitive_to_bin("uint16", obj.servo5_raw, 2))

    # member: servo6_raw, type: uint16 (primitive), offset: 16, size: 2
    allocator = add_binary(allocator, parent_off + 16, primitive_to_bin("uint16", obj.servo6_raw, 2))

    # member: servo7_raw, type: uint16 (primitive), offset: 18, size: 2
    allocator = add_binary(allocator, parent_off + 18, primitive_to_bin("uint16", obj.servo7_raw, 2))

    # member: servo8_raw, type: uint16 (primitive), offset: 20, size: 2
    allocator = add_binary(allocator, parent_off + 20, primitive_to_bin("uint16", obj.servo8_raw, 2))

    # member: servo9_raw, type: uint16 (primitive), offset: 22, size: 2
    allocator = add_binary(allocator, parent_off + 22, primitive_to_bin("uint16", obj.servo9_raw, 2))

    # member: servo10_raw, type: uint16 (primitive), offset: 24, size: 2
    allocator = add_binary(allocator, parent_off + 24, primitive_to_bin("uint16", obj.servo10_raw, 2))

    # member: servo11_raw, type: uint16 (primitive), offset: 26, size: 2
    allocator = add_binary(allocator, parent_off + 26, primitive_to_bin("uint16", obj.servo11_raw, 2))

    # member: servo12_raw, type: uint16 (primitive), offset: 28, size: 2
    allocator = add_binary(allocator, parent_off + 28, primitive_to_bin("uint16", obj.servo12_raw, 2))

    # member: servo13_raw, type: uint16 (primitive), offset: 30, size: 2
    allocator = add_binary(allocator, parent_off + 30, primitive_to_bin("uint16", obj.servo13_raw, 2))

    # member: servo14_raw, type: uint16 (primitive), offset: 32, size: 2
    allocator = add_binary(allocator, parent_off + 32, primitive_to_bin("uint16", obj.servo14_raw, 2))

    # member: servo15_raw, type: uint16 (primitive), offset: 34, size: 2
    allocator = add_binary(allocator, parent_off + 34, primitive_to_bin("uint16", obj.servo15_raw, 2))

    # member: servo16_raw, type: uint16 (primitive), offset: 36, size: 2
    allocator = add_binary(allocator, parent_off + 36, primitive_to_bin("uint16", obj.servo16_raw, 2))

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
