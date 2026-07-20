defmodule HakoPdu.SensorMsgs.BatteryStateConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_battery_state(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.SensorMsgs.BatteryState.new()
    binary_read_recursive_battery_state(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_battery_state(obj) do
    {base_data, heap_data} = binary_write_recursive_battery_state(0, "", "", obj)
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

  def binary_read_recursive_battery_state(meta, binary_data, obj, base_off) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    header =
      HakoPdu.StdMsgs.HeaderConverter.binary_read_recursive_header(
        meta,
        binary_data,
        HakoPdu.StdMsgs.Header.new(),
        base_off + 0
      )

    # member: voltage, type: float32 (primitive), offset: 136, size: 4
    voltage = read_primitive("float32", binary_part(binary_data, base_off + 136, 4))

    # member: temperature, type: float32 (primitive), offset: 140, size: 4
    temperature = read_primitive("float32", binary_part(binary_data, base_off + 140, 4))

    # member: current, type: float32 (primitive), offset: 144, size: 4
    current = read_primitive("float32", binary_part(binary_data, base_off + 144, 4))

    # member: charge, type: float32 (primitive), offset: 148, size: 4
    charge = read_primitive("float32", binary_part(binary_data, base_off + 148, 4))

    # member: capacity, type: float32 (primitive), offset: 152, size: 4
    capacity = read_primitive("float32", binary_part(binary_data, base_off + 152, 4))

    # member: design_capacity, type: float32 (primitive), offset: 156, size: 4
    design_capacity = read_primitive("float32", binary_part(binary_data, base_off + 156, 4))

    # member: percentage, type: float32 (primitive), offset: 160, size: 4
    percentage = read_primitive("float32", binary_part(binary_data, base_off + 160, 4))

    # member: power_supply_status, type: uint8 (primitive), offset: 164, size: 1
    power_supply_status = read_primitive("uint8", binary_part(binary_data, base_off + 164, 1))

    # member: power_supply_health, type: uint8 (primitive), offset: 165, size: 1
    power_supply_health = read_primitive("uint8", binary_part(binary_data, base_off + 165, 1))

    # member: power_supply_technology, type: uint8 (primitive), offset: 166, size: 1
    power_supply_technology = read_primitive("uint8", binary_part(binary_data, base_off + 166, 1))

    # member: present, type: bool (primitive), offset: 168, size: 4
    present = read_primitive("bool", binary_part(binary_data, base_off + 168, 4))

    # member: cell_voltage, type: float32 (primitive), offset: 172, size: 4
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 172, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 172 + 4, 4))
    cell_voltage = read_primitive_array("float32", binary_part(binary_data, meta.heap_off + offset_from_heap, 4 * array_size), array_size, 4)

    # member: cell_temperature, type: float32 (primitive), offset: 180, size: 4
    array_size = read_primitive("int32", binary_part(binary_data, base_off + 180, 4))
    offset_from_heap = read_primitive("int32", binary_part(binary_data, base_off + 180 + 4, 4))
    cell_temperature = read_primitive_array("float32", binary_part(binary_data, meta.heap_off + offset_from_heap, 4 * array_size), array_size, 4)

    # member: location, type: string (primitive), offset: 188, size: 128
    location = read_primitive("string", binary_part(binary_data, base_off + 188, 128))

    # member: serial_number, type: string (primitive), offset: 316, size: 128
    serial_number = read_primitive("string", binary_part(binary_data, base_off + 316, 128))

    struct(obj, %{

      header: header,

      voltage: voltage,

      temperature: temperature,

      current: current,

      charge: charge,

      capacity: capacity,

      design_capacity: design_capacity,

      percentage: percentage,

      power_supply_status: power_supply_status,

      power_supply_health: power_supply_health,

      power_supply_technology: power_supply_technology,

      present: present,

      cell_voltage: cell_voltage,

      cell_temperature: cell_temperature,

      location: location,

      serial_number: serial_number

    })
  end

  def binary_write_recursive_battery_state(parent_off, heap_data, allocator, obj) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    {allocator, heap_data} =
      HakoPdu.StdMsgs.HeaderConverter.binary_write_recursive_header(
        parent_off + 0,
        heap_data,
        allocator,
        obj.header
      )

    # member: voltage, type: float32 (primitive), offset: 136, size: 4
    allocator = add_binary(allocator, parent_off + 136, primitive_to_bin("float32", obj.voltage, 4))

    # member: temperature, type: float32 (primitive), offset: 140, size: 4
    allocator = add_binary(allocator, parent_off + 140, primitive_to_bin("float32", obj.temperature, 4))

    # member: current, type: float32 (primitive), offset: 144, size: 4
    allocator = add_binary(allocator, parent_off + 144, primitive_to_bin("float32", obj.current, 4))

    # member: charge, type: float32 (primitive), offset: 148, size: 4
    allocator = add_binary(allocator, parent_off + 148, primitive_to_bin("float32", obj.charge, 4))

    # member: capacity, type: float32 (primitive), offset: 152, size: 4
    allocator = add_binary(allocator, parent_off + 152, primitive_to_bin("float32", obj.capacity, 4))

    # member: design_capacity, type: float32 (primitive), offset: 156, size: 4
    allocator = add_binary(allocator, parent_off + 156, primitive_to_bin("float32", obj.design_capacity, 4))

    # member: percentage, type: float32 (primitive), offset: 160, size: 4
    allocator = add_binary(allocator, parent_off + 160, primitive_to_bin("float32", obj.percentage, 4))

    # member: power_supply_status, type: uint8 (primitive), offset: 164, size: 1
    allocator = add_binary(allocator, parent_off + 164, primitive_to_bin("uint8", obj.power_supply_status, 1))

    # member: power_supply_health, type: uint8 (primitive), offset: 165, size: 1
    allocator = add_binary(allocator, parent_off + 165, primitive_to_bin("uint8", obj.power_supply_health, 1))

    # member: power_supply_technology, type: uint8 (primitive), offset: 166, size: 1
    allocator = add_binary(allocator, parent_off + 166, primitive_to_bin("uint8", obj.power_supply_technology, 1))

    # member: present, type: bool (primitive), offset: 168, size: 4
    allocator = add_binary(allocator, parent_off + 168, primitive_to_bin("bool", obj.present, 4))

    # member: cell_voltage, type: float32 (primitive), offset: 172, size: 4
    offset_from_heap = byte_size(heap_data)
    values = obj.cell_voltage || []
    allocator = add_binary(allocator, parent_off + 172, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("float32", values, 4))

    # member: cell_temperature, type: float32 (primitive), offset: 180, size: 4
    offset_from_heap = byte_size(heap_data)
    values = obj.cell_temperature || []
    allocator = add_binary(allocator, parent_off + 180, <<length(values)::little-signed-integer-size(32), offset_from_heap::little-signed-integer-size(32)>>)
    heap_data = add_binary(heap_data, offset_from_heap, primitive_array_to_bin("float32", values, 4))

    # member: location, type: string (primitive), offset: 188, size: 128
    allocator = add_binary(allocator, parent_off + 188, primitive_to_bin("string", obj.location, 128))

    # member: serial_number, type: string (primitive), offset: 316, size: 128
    allocator = add_binary(allocator, parent_off + 316, primitive_to_bin("string", obj.serial_number, 128))

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
