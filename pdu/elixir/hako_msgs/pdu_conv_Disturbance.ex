defmodule HakoPdu.HakoMsgs.DisturbanceConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_disturbance(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMsgs.Disturbance.new()
    binary_read_recursive_disturbance(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_disturbance(obj) do
    {base_data, heap_data} = binary_write_recursive_disturbance(0, "", "", obj)
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

  def binary_read_recursive_disturbance(meta, binary_data, obj, base_off) do
    # member: d_temp, type: hako_msgs/DisturbanceTemperature (struct), offset: 0, size: 8
    d_temp =
      HakoPdu.HakoMsgs.DisturbanceTemperatureConverter.binary_read_recursive_disturbance_temperature(
        meta,
        binary_data,
        HakoPdu.HakoMsgs.DisturbanceTemperature.new(),
        base_off + 0
      )

    # member: d_wind, type: hako_msgs/DisturbanceWind (struct), offset: 8, size: 24
    d_wind =
      HakoPdu.HakoMsgs.DisturbanceWindConverter.binary_read_recursive_disturbance_wind(
        meta,
        binary_data,
        HakoPdu.HakoMsgs.DisturbanceWind.new(),
        base_off + 8
      )

    # member: d_atm, type: hako_msgs/DisturbanceAtm (struct), offset: 32, size: 8
    d_atm =
      HakoPdu.HakoMsgs.DisturbanceAtmConverter.binary_read_recursive_disturbance_atm(
        meta,
        binary_data,
        HakoPdu.HakoMsgs.DisturbanceAtm.new(),
        base_off + 32
      )

    # member: d_boundary, type: hako_msgs/DisturbanceBoundary (struct), offset: 40, size: 48
    d_boundary =
      HakoPdu.HakoMsgs.DisturbanceBoundaryConverter.binary_read_recursive_disturbance_boundary(
        meta,
        binary_data,
        HakoPdu.HakoMsgs.DisturbanceBoundary.new(),
        base_off + 40
      )

    # member: d_user_custom, type: hako_msgs/DisturbanceUserCustom (struct), offset: 88, size: 8
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 88, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 88 + 4, 4))
    d_user_custom =
      range_indices(array_size)
      |> Enum.map(fn i ->
        HakoPdu.HakoMsgs.DisturbanceUserCustomConverter.binary_read_recursive_disturbance_user_custom(
          meta,
          binary_data,
          HakoPdu.HakoMsgs.DisturbanceUserCustom.new(),
          meta.heap_off + offset_from_heap + i * 8
        )
      end)

    struct(obj, %{

      d_temp: d_temp,

      d_wind: d_wind,

      d_atm: d_atm,

      d_boundary: d_boundary,

      d_user_custom: d_user_custom

    })
  end

  def binary_write_recursive_disturbance(parent_off, heap_data, allocator, obj) do
    # member: d_temp, type: hako_msgs/DisturbanceTemperature (struct), offset: 0, size: 8
    {allocator, heap_data} =
      HakoPdu.HakoMsgs.DisturbanceTemperatureConverter.binary_write_recursive_disturbance_temperature(
        parent_off + 0,
        heap_data,
        allocator,
        obj.d_temp
      )

    # member: d_wind, type: hako_msgs/DisturbanceWind (struct), offset: 8, size: 24
    {allocator, heap_data} =
      HakoPdu.HakoMsgs.DisturbanceWindConverter.binary_write_recursive_disturbance_wind(
        parent_off + 8,
        heap_data,
        allocator,
        obj.d_wind
      )

    # member: d_atm, type: hako_msgs/DisturbanceAtm (struct), offset: 32, size: 8
    {allocator, heap_data} =
      HakoPdu.HakoMsgs.DisturbanceAtmConverter.binary_write_recursive_disturbance_atm(
        parent_off + 32,
        heap_data,
        allocator,
        obj.d_atm
      )

    # member: d_boundary, type: hako_msgs/DisturbanceBoundary (struct), offset: 40, size: 48
    {allocator, heap_data} =
      HakoPdu.HakoMsgs.DisturbanceBoundaryConverter.binary_write_recursive_disturbance_boundary(
        parent_off + 40,
        heap_data,
        allocator,
        obj.d_boundary
      )

    # member: d_user_custom, type: hako_msgs/DisturbanceUserCustom (struct), offset: 88, size: 8
    offset_from_heap = byte_size(heap_data)
    values = obj.d_user_custom || []
    allocator = add_binary(allocator, parent_off + 88, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, :binary.copy(<<0>>, length(values) * 8))
    heap_data =
      values
      |> Enum.with_index()
      |> Enum.reduce(heap_data, fn {child, i}, acc_heap ->
        {new_heap_allocator, new_heap_data} =
          HakoPdu.HakoMsgs.DisturbanceUserCustomConverter.binary_write_recursive_disturbance_user_custom(
            offset_from_heap + i * 8,
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
