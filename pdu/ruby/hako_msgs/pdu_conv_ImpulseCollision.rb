require_relative 'pdu_type_ImpulseCollision'
require_relative '../geometry_msgs/pdu_type_Point'
require_relative '../geometry_msgs/pdu_conv_Point'
require_relative '../geometry_msgs/pdu_type_Vector3'
require_relative '../geometry_msgs/pdu_conv_Vector3'


module HakoPdu::HakoMsgs::ImpulseCollisionConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_impulse_collision(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoMsgs::ImpulseCollision.new
    binary_read_recursive_impulse_collision(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_impulse_collision(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_impulse_collision(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_impulse_collision(meta, binary_data, obj, base_off)
    # member: collision, type: bool (primitive), offset: 0, size: 4
    obj.collision = read_primitive('bool', binary_data.byteslice(base_off + 0, 4))

    # member: is_target_static, type: bool (primitive), offset: 4, size: 4
    obj.is_target_static = read_primitive('bool', binary_data.byteslice(base_off + 4, 4))

    # member: restitution_coefficient, type: float64 (primitive), offset: 8, size: 8
    obj.restitution_coefficient = read_primitive('float64', binary_data.byteslice(base_off + 8, 8))

    # member: self_contact_vector, type: geometry_msgs/Point (struct), offset: 16, size: 24
    obj.self_contact_vector = HakoPdu::GeometryMsgs::Point.new
    HakoPdu::GeometryMsgs::PointConverter.binary_read_recursive_point(meta, binary_data, obj.self_contact_vector, base_off + 16)

    # member: normal, type: geometry_msgs/Vector3 (struct), offset: 40, size: 24
    obj.normal = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.normal, base_off + 40)

    # member: target_contact_vector, type: geometry_msgs/Point (struct), offset: 64, size: 24
    obj.target_contact_vector = HakoPdu::GeometryMsgs::Point.new
    HakoPdu::GeometryMsgs::PointConverter.binary_read_recursive_point(meta, binary_data, obj.target_contact_vector, base_off + 64)

    # member: target_velocity, type: geometry_msgs/Vector3 (struct), offset: 88, size: 24
    obj.target_velocity = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.target_velocity, base_off + 88)

    # member: target_angular_velocity, type: geometry_msgs/Vector3 (struct), offset: 112, size: 24
    obj.target_angular_velocity = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.target_angular_velocity, base_off + 112)

    # member: target_euler, type: geometry_msgs/Vector3 (struct), offset: 136, size: 24
    obj.target_euler = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.target_euler, base_off + 136)

    # member: target_inertia, type: geometry_msgs/Vector3 (struct), offset: 160, size: 24
    obj.target_inertia = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.target_inertia, base_off + 160)

    # member: target_mass, type: float64 (primitive), offset: 184, size: 8
    obj.target_mass = read_primitive('float64', binary_data.byteslice(base_off + 184, 8))

    obj
  end

  def self.binary_write_recursive_impulse_collision(parent_off, heap_data, allocator, obj)
    # member: collision, type: bool (primitive), offset: 0, size: 4
    add_binary(allocator, parent_off + 0, primitive_to_bin('bool', obj.collision, 4))

    # member: is_target_static, type: bool (primitive), offset: 4, size: 4
    add_binary(allocator, parent_off + 4, primitive_to_bin('bool', obj.is_target_static, 4))

    # member: restitution_coefficient, type: float64 (primitive), offset: 8, size: 8
    add_binary(allocator, parent_off + 8, primitive_to_bin('float64', obj.restitution_coefficient, 8))

    # member: self_contact_vector, type: geometry_msgs/Point (struct), offset: 16, size: 24
    HakoPdu::GeometryMsgs::PointConverter.binary_write_recursive_point(parent_off + 16, heap_data, allocator, obj.self_contact_vector)

    # member: normal, type: geometry_msgs/Vector3 (struct), offset: 40, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 40, heap_data, allocator, obj.normal)

    # member: target_contact_vector, type: geometry_msgs/Point (struct), offset: 64, size: 24
    HakoPdu::GeometryMsgs::PointConverter.binary_write_recursive_point(parent_off + 64, heap_data, allocator, obj.target_contact_vector)

    # member: target_velocity, type: geometry_msgs/Vector3 (struct), offset: 88, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 88, heap_data, allocator, obj.target_velocity)

    # member: target_angular_velocity, type: geometry_msgs/Vector3 (struct), offset: 112, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 112, heap_data, allocator, obj.target_angular_velocity)

    # member: target_euler, type: geometry_msgs/Vector3 (struct), offset: 136, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 136, heap_data, allocator, obj.target_euler)

    # member: target_inertia, type: geometry_msgs/Vector3 (struct), offset: 160, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 160, heap_data, allocator, obj.target_inertia)

    # member: target_mass, type: float64 (primitive), offset: 184, size: 8
    add_binary(allocator, parent_off + 184, primitive_to_bin('float64', obj.target_mass, 8))

    obj
  end

  def self.load_pdu_meta(binary_data)
    bytes = binary_data.b
    raise ArgumentError, 'PDU is too small for metadata' if bytes.bytesize < PDU_META_DATA_SIZE
    magic, version, base_off, heap_off, total_size = bytes.unpack('V5')
    if magic != PDU_META_DATA_MAGICNO || version != PDU_META_DATA_VERSION
      raise ArgumentError, "Invalid PDU metadata: magic=#{magic.to_s(16)}, version=#{version}"
    end
    { magic: magic, version: version, base_off: base_off, heap_off: heap_off, total_size: total_size }
  end

  def self.add_binary(buffer, offset, data)
    data = data.b
    return offset if data.bytesize == 0
    if buffer.bytesize < offset
      buffer << "\x00".b * (offset - buffer.bytesize)
    end
    end_offset = offset + data.bytesize
    if buffer.bytesize < end_offset
      buffer << "\x00".b * (end_offset - buffer.bytesize)
    end
    buffer[offset, data.bytesize] = data
    offset
  end

  def self.read_primitive(type, bytes)
    case type
    when 'bool'
      bytes.unpack1('L<') != 0
    when 'byte', 'uint8'
      bytes.unpack1('C')
    when 'char'
      bytes.unpack1('C').chr
    when 'int8'
      bytes.unpack1('c')
    when 'int16'
      bytes.unpack1('s<')
    when 'uint16'
      bytes.unpack1('S<')
    when 'int32'
      bytes.unpack1('l<')
    when 'uint32'
      bytes.unpack1('L<')
    when 'int64'
      bytes.unpack1('q<')
    when 'uint64'
      bytes.unpack1('Q<')
    when 'float32'
      bytes.unpack1('e')
    when 'float64'
      bytes.unpack1('E')
    when 'string'
      bytes.split("\x00".b, 2).first.force_encoding('UTF-8')
    else
      raise ArgumentError, "Unsupported primitive type: #{type}"
    end
  end

  def self.primitive_to_bin(type, value, size = nil)
    bytes = case type
            when 'bool'
              [value ? 1 : 0].pack('L<')
            when 'byte', 'uint8'
              [value].pack('C')
            when 'char'
              [(value || "\x00").to_s.bytes.first || 0].pack('C')
            when 'int8'
              [value].pack('c')
            when 'int16'
              [value].pack('s<')
            when 'uint16'
              [value].pack('S<')
            when 'int32'
              [value].pack('l<')
            when 'uint32'
              [value].pack('L<')
            when 'int64'
              [value].pack('q<')
            when 'uint64'
              [value].pack('Q<')
            when 'float32'
              [value].pack('e')
            when 'float64'
              [value].pack('E')
            when 'string'
              value.to_s.b + "\x00".b
            else
              raise ArgumentError, "Unsupported primitive type: #{type}"
            end
    return bytes unless size
    bytes = bytes.byteslice(0, size) if bytes.bytesize > size
    bytes + ("\x00".b * [size - bytes.bytesize, 0].max)
  end

  def self.read_primitive_array(type, bytes, count, element_size)
    count.times.map do |i|
      read_primitive(type, bytes.byteslice(i * element_size, element_size))
    end
  end

  def self.primitive_array_to_bin(type, values, element_size = nil)
    (values || []).map { |value| primitive_to_bin(type, value, element_size) }.join.b
  end
end
