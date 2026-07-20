defmodule HakoPdu.MavrosMsgs.AttitudeTargetConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_attitude_target(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.MavrosMsgs.AttitudeTarget.new()
    binary_read_recursive_attitude_target(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_attitude_target(obj) do
    {base_data, heap_data} = binary_write_recursive_attitude_target(0, "", "", obj)
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

  def binary_read_recursive_attitude_target(meta, binary_data, obj, base_off) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    header =
      HakoPdu.StdMsgs.HeaderConverter.binary_read_recursive_header(
        meta,
        binary_data,
        HakoPdu.StdMsgs.Header.new(),
        base_off + 0
      )

    # member: type_mask, type: uint8 (primitive), offset: 136, size: 1
    type_mask = read_primitive("uint8", binary_part(binary_data, base_off + 136, 1))

    # member: orientation, type: geometry_msgs/Quaternion (struct), offset: 144, size: 32
    orientation =
      HakoPdu.GeometryMsgs.QuaternionConverter.binary_read_recursive_quaternion(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Quaternion.new(),
        base_off + 144
      )

    # member: body_rate, type: geometry_msgs/Vector3 (struct), offset: 176, size: 24
    body_rate =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 176
      )

    # member: thrust, type: float32 (primitive), offset: 200, size: 4
    thrust = read_primitive("float32", binary_part(binary_data, base_off + 200, 4))

    struct(obj, %{

      header: header,

      type_mask: type_mask,

      orientation: orientation,

      body_rate: body_rate,

      thrust: thrust

    })
  end

  def binary_write_recursive_attitude_target(parent_off, heap_data, allocator, obj) do
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    {allocator, heap_data} =
      HakoPdu.StdMsgs.HeaderConverter.binary_write_recursive_header(
        parent_off + 0,
        heap_data,
        allocator,
        obj.header
      )

    # member: type_mask, type: uint8 (primitive), offset: 136, size: 1
    allocator = add_binary(allocator, parent_off + 136, primitive_to_bin("uint8", obj.type_mask, 1))

    # member: orientation, type: geometry_msgs/Quaternion (struct), offset: 144, size: 32
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.QuaternionConverter.binary_write_recursive_quaternion(
        parent_off + 144,
        heap_data,
        allocator,
        obj.orientation
      )

    # member: body_rate, type: geometry_msgs/Vector3 (struct), offset: 176, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 176,
        heap_data,
        allocator,
        obj.body_rate
      )

    # member: thrust, type: float32 (primitive), offset: 200, size: 4
    allocator = add_binary(allocator, parent_off + 200, primitive_to_bin("float32", obj.thrust, 4))

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
