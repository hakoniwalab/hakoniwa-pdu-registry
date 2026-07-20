defmodule HakoPdu.Ev3Msgs.Ev3PduActuatorConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_ev3_pdu_actuator(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.Ev3Msgs.Ev3PduActuator.new()
    binary_read_recursive_ev3_pdu_actuator(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_ev3_pdu_actuator(obj) do
    {base_data, heap_data} = binary_write_recursive_ev3_pdu_actuator(0, "", "", obj)
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

  def binary_read_recursive_ev3_pdu_actuator(meta, binary_data, obj, base_off) do
    # member: head, type: Ev3PduActuatorHeader (struct), offset: 0, size: 152
    head =
      HakoPdu.Ev3Msgs.Ev3PduActuatorHeaderConverter.binary_read_recursive_ev3_pdu_actuator_header(
        meta,
        binary_data,
        HakoPdu.Ev3Msgs.Ev3PduActuatorHeader.new(),
        base_off + 0
      )

    # member: leds, type: uint8 (primitive), offset: 152, size: 1
    leds = read_primitive_array("uint8", binary_part(binary_data, base_off + 152, 1), 1, div(1, 1))

    # member: motors, type: Ev3PduMotor (struct), offset: 156, size: 36
    motors =
      Enum.map(0..(3 - 1), fn i ->
        HakoPdu.Ev3Msgs.Ev3PduMotorConverter.binary_read_recursive_ev3_pdu_motor(
          meta,
          binary_data,
          HakoPdu.Ev3Msgs.Ev3PduMotor.new(),
          base_off + 156 + i * div(36, 3)
        )
      end)

    # member: gyro_reset, type: uint32 (primitive), offset: 192, size: 4
    gyro_reset = read_primitive("uint32", binary_part(binary_data, base_off + 192, 4))

    struct(obj, %{

      head: head,

      leds: leds,

      motors: motors,

      gyro_reset: gyro_reset

    })
  end

  def binary_write_recursive_ev3_pdu_actuator(parent_off, heap_data, allocator, obj) do
    # member: head, type: Ev3PduActuatorHeader (struct), offset: 0, size: 152
    {allocator, heap_data} =
      HakoPdu.Ev3Msgs.Ev3PduActuatorHeaderConverter.binary_write_recursive_ev3_pdu_actuator_header(
        parent_off + 0,
        heap_data,
        allocator,
        obj.head
      )

    # member: leds, type: uint8 (primitive), offset: 152, size: 1
    allocator = add_binary(allocator, parent_off + 152, primitive_array_to_bin("uint8", obj.leds, div(1, 1)))

    # member: motors, type: Ev3PduMotor (struct), offset: 156, size: 36
    {allocator, heap_data} =
      (obj.motors || [])
      |> Enum.with_index()
      |> Enum.reduce({allocator, heap_data}, fn {child, i}, {acc_allocator, acc_heap} ->
        HakoPdu.Ev3Msgs.Ev3PduMotorConverter.binary_write_recursive_ev3_pdu_motor(
          parent_off + 156 + i * div(36, 3),
          acc_heap,
          acc_allocator,
          child
        )
      end)

    # member: gyro_reset, type: uint32 (primitive), offset: 192, size: 4
    allocator = add_binary(allocator, parent_off + 192, primitive_to_bin("uint32", obj.gyro_reset, 4))

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
