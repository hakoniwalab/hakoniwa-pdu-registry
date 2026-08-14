defmodule HakoPdu.HakoMsgs.ImpulseCollisionConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_impulse_collision(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoMsgs.ImpulseCollision.new()
    binary_read_recursive_impulse_collision(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_impulse_collision(obj) do
    {base_data, heap_data} = binary_write_recursive_impulse_collision(0, "", "", obj)
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

  def binary_read_recursive_impulse_collision(meta, binary_data, obj, base_off) do
    # member: collision, type: bool (primitive), offset: 0, size: 4
    collision = read_primitive("bool", binary_part(binary_data, base_off + 0, 4))

    # member: is_target_static, type: bool (primitive), offset: 4, size: 4
    is_target_static = read_primitive("bool", binary_part(binary_data, base_off + 4, 4))

    # member: restitution_coefficient, type: float64 (primitive), offset: 8, size: 8
    restitution_coefficient = read_primitive("float64", binary_part(binary_data, base_off + 8, 8))

    # member: self_contact_vector, type: geometry_msgs/Point (struct), offset: 16, size: 24
    self_contact_vector =
      HakoPdu.GeometryMsgs.PointConverter.binary_read_recursive_point(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Point.new(),
        base_off + 16
      )

    # member: normal, type: geometry_msgs/Vector3 (struct), offset: 40, size: 24
    normal =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 40
      )

    # member: target_contact_vector, type: geometry_msgs/Point (struct), offset: 64, size: 24
    target_contact_vector =
      HakoPdu.GeometryMsgs.PointConverter.binary_read_recursive_point(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Point.new(),
        base_off + 64
      )

    # member: target_velocity, type: geometry_msgs/Vector3 (struct), offset: 88, size: 24
    target_velocity =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 88
      )

    # member: target_angular_velocity, type: geometry_msgs/Vector3 (struct), offset: 112, size: 24
    target_angular_velocity =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 112
      )

    # member: target_euler, type: geometry_msgs/Vector3 (struct), offset: 136, size: 24
    target_euler =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 136
      )

    # member: target_inertia, type: geometry_msgs/Vector3 (struct), offset: 160, size: 24
    target_inertia =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_read_recursive_vector3(
        meta,
        binary_data,
        HakoPdu.GeometryMsgs.Vector3.new(),
        base_off + 160
      )

    # member: target_mass, type: float64 (primitive), offset: 184, size: 8
    target_mass = read_primitive("float64", binary_part(binary_data, base_off + 184, 8))

    struct(obj, %{

      collision: collision,

      is_target_static: is_target_static,

      restitution_coefficient: restitution_coefficient,

      self_contact_vector: self_contact_vector,

      normal: normal,

      target_contact_vector: target_contact_vector,

      target_velocity: target_velocity,

      target_angular_velocity: target_angular_velocity,

      target_euler: target_euler,

      target_inertia: target_inertia,

      target_mass: target_mass

    })
  end

  def binary_write_recursive_impulse_collision(parent_off, heap_data, allocator, obj) do
    # member: collision, type: bool (primitive), offset: 0, size: 4
    allocator = add_binary(allocator, parent_off + 0, primitive_to_bin("bool", obj.collision, 4))

    # member: is_target_static, type: bool (primitive), offset: 4, size: 4
    allocator = add_binary(allocator, parent_off + 4, primitive_to_bin("bool", obj.is_target_static, 4))

    # member: restitution_coefficient, type: float64 (primitive), offset: 8, size: 8
    allocator = add_binary(allocator, parent_off + 8, primitive_to_bin("float64", obj.restitution_coefficient, 8))

    # member: self_contact_vector, type: geometry_msgs/Point (struct), offset: 16, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.PointConverter.binary_write_recursive_point(
        parent_off + 16,
        heap_data,
        allocator,
        obj.self_contact_vector
      )

    # member: normal, type: geometry_msgs/Vector3 (struct), offset: 40, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 40,
        heap_data,
        allocator,
        obj.normal
      )

    # member: target_contact_vector, type: geometry_msgs/Point (struct), offset: 64, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.PointConverter.binary_write_recursive_point(
        parent_off + 64,
        heap_data,
        allocator,
        obj.target_contact_vector
      )

    # member: target_velocity, type: geometry_msgs/Vector3 (struct), offset: 88, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 88,
        heap_data,
        allocator,
        obj.target_velocity
      )

    # member: target_angular_velocity, type: geometry_msgs/Vector3 (struct), offset: 112, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 112,
        heap_data,
        allocator,
        obj.target_angular_velocity
      )

    # member: target_euler, type: geometry_msgs/Vector3 (struct), offset: 136, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 136,
        heap_data,
        allocator,
        obj.target_euler
      )

    # member: target_inertia, type: geometry_msgs/Vector3 (struct), offset: 160, size: 24
    {allocator, heap_data} =
      HakoPdu.GeometryMsgs.Vector3Converter.binary_write_recursive_vector3(
        parent_off + 160,
        heap_data,
        allocator,
        obj.target_inertia
      )

    # member: target_mass, type: float64 (primitive), offset: 184, size: 8
    allocator = add_binary(allocator, parent_off + 184, primitive_to_bin("float64", obj.target_mass, 8))

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
