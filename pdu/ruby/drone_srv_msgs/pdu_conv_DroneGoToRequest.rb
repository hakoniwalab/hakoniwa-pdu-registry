require_relative 'pdu_type_DroneGoToRequest'
require_relative '../geometry_msgs/pdu_type_Vector3'
require_relative '../geometry_msgs/pdu_conv_Vector3'


module HakoPdu::DroneSrvMsgs::DroneGoToRequestConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_drone_go_to_request(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::DroneSrvMsgs::DroneGoToRequest.new
    binary_read_recursive_drone_go_to_request(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_drone_go_to_request(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_drone_go_to_request(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_drone_go_to_request(meta, binary_data, obj, base_off)
    # member: drone_name, type: string (primitive), offset: 0, size: 128
    obj.drone_name = read_primitive('string', binary_data.byteslice(base_off + 0, 128))

    # member: target_pose, type: geometry_msgs/Vector3 (struct), offset: 128, size: 24
    obj.target_pose = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.target_pose, base_off + 128)

    # member: speed_m_s, type: float32 (primitive), offset: 152, size: 4
    obj.speed_m_s = read_primitive('float32', binary_data.byteslice(base_off + 152, 4))

    # member: yaw_deg, type: float32 (primitive), offset: 156, size: 4
    obj.yaw_deg = read_primitive('float32', binary_data.byteslice(base_off + 156, 4))

    # member: tolerance_m, type: float32 (primitive), offset: 160, size: 4
    obj.tolerance_m = read_primitive('float32', binary_data.byteslice(base_off + 160, 4))

    # member: timeout_sec, type: float32 (primitive), offset: 164, size: 4
    obj.timeout_sec = read_primitive('float32', binary_data.byteslice(base_off + 164, 4))

    obj
  end

  def self.binary_write_recursive_drone_go_to_request(parent_off, heap_data, allocator, obj)
    # member: drone_name, type: string (primitive), offset: 0, size: 128
    add_binary(allocator, parent_off + 0, primitive_to_bin('string', obj.drone_name, 128))

    # member: target_pose, type: geometry_msgs/Vector3 (struct), offset: 128, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 128, heap_data, allocator, obj.target_pose)

    # member: speed_m_s, type: float32 (primitive), offset: 152, size: 4
    add_binary(allocator, parent_off + 152, primitive_to_bin('float32', obj.speed_m_s, 4))

    # member: yaw_deg, type: float32 (primitive), offset: 156, size: 4
    add_binary(allocator, parent_off + 156, primitive_to_bin('float32', obj.yaw_deg, 4))

    # member: tolerance_m, type: float32 (primitive), offset: 160, size: 4
    add_binary(allocator, parent_off + 160, primitive_to_bin('float32', obj.tolerance_m, 4))

    # member: timeout_sec, type: float32 (primitive), offset: 164, size: 4
    add_binary(allocator, parent_off + 164, primitive_to_bin('float32', obj.timeout_sec, 4))

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
