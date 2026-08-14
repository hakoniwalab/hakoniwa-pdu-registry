require_relative 'pdu_type_GlobalPositionTarget'
require_relative '../std_msgs/pdu_type_Header'
require_relative '../std_msgs/pdu_conv_Header'
require_relative '../geometry_msgs/pdu_type_Vector3'
require_relative '../geometry_msgs/pdu_conv_Vector3'


module HakoPdu::MavrosMsgs::GlobalPositionTargetConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_global_position_target(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::MavrosMsgs::GlobalPositionTarget.new
    binary_read_recursive_global_position_target(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_global_position_target(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_global_position_target(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_global_position_target(meta, binary_data, obj, base_off)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    obj.header = HakoPdu::StdMsgs::Header.new
    HakoPdu::StdMsgs::HeaderConverter.binary_read_recursive_header(meta, binary_data, obj.header, base_off + 0)

    # member: coordinate_frame, type: uint8 (primitive), offset: 136, size: 1
    obj.coordinate_frame = read_primitive('uint8', binary_data.byteslice(base_off + 136, 1))

    # member: type_mask, type: uint16 (primitive), offset: 138, size: 2
    obj.type_mask = read_primitive('uint16', binary_data.byteslice(base_off + 138, 2))

    # member: latitude, type: float64 (primitive), offset: 144, size: 8
    obj.latitude = read_primitive('float64', binary_data.byteslice(base_off + 144, 8))

    # member: longitude, type: float64 (primitive), offset: 152, size: 8
    obj.longitude = read_primitive('float64', binary_data.byteslice(base_off + 152, 8))

    # member: altitude, type: float32 (primitive), offset: 160, size: 4
    obj.altitude = read_primitive('float32', binary_data.byteslice(base_off + 160, 4))

    # member: velocity, type: geometry_msgs/Vector3 (struct), offset: 168, size: 24
    obj.velocity = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.velocity, base_off + 168)

    # member: acceleration_or_force, type: geometry_msgs/Vector3 (struct), offset: 192, size: 24
    obj.acceleration_or_force = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.acceleration_or_force, base_off + 192)

    # member: yaw, type: float32 (primitive), offset: 216, size: 4
    obj.yaw = read_primitive('float32', binary_data.byteslice(base_off + 216, 4))

    # member: yaw_rate, type: float32 (primitive), offset: 220, size: 4
    obj.yaw_rate = read_primitive('float32', binary_data.byteslice(base_off + 220, 4))

    obj
  end

  def self.binary_write_recursive_global_position_target(parent_off, heap_data, allocator, obj)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    HakoPdu::StdMsgs::HeaderConverter.binary_write_recursive_header(parent_off + 0, heap_data, allocator, obj.header)

    # member: coordinate_frame, type: uint8 (primitive), offset: 136, size: 1
    add_binary(allocator, parent_off + 136, primitive_to_bin('uint8', obj.coordinate_frame, 1))

    # member: type_mask, type: uint16 (primitive), offset: 138, size: 2
    add_binary(allocator, parent_off + 138, primitive_to_bin('uint16', obj.type_mask, 2))

    # member: latitude, type: float64 (primitive), offset: 144, size: 8
    add_binary(allocator, parent_off + 144, primitive_to_bin('float64', obj.latitude, 8))

    # member: longitude, type: float64 (primitive), offset: 152, size: 8
    add_binary(allocator, parent_off + 152, primitive_to_bin('float64', obj.longitude, 8))

    # member: altitude, type: float32 (primitive), offset: 160, size: 4
    add_binary(allocator, parent_off + 160, primitive_to_bin('float32', obj.altitude, 4))

    # member: velocity, type: geometry_msgs/Vector3 (struct), offset: 168, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 168, heap_data, allocator, obj.velocity)

    # member: acceleration_or_force, type: geometry_msgs/Vector3 (struct), offset: 192, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 192, heap_data, allocator, obj.acceleration_or_force)

    # member: yaw, type: float32 (primitive), offset: 216, size: 4
    add_binary(allocator, parent_off + 216, primitive_to_bin('float32', obj.yaw, 4))

    # member: yaw_rate, type: float32 (primitive), offset: 220, size: 4
    add_binary(allocator, parent_off + 220, primitive_to_bin('float32', obj.yaw_rate, 4))

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
    when 'byte', 'char', 'uint8'
      bytes.unpack1('C')
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
            when 'byte', 'char', 'uint8'
              [value].pack('C')
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
