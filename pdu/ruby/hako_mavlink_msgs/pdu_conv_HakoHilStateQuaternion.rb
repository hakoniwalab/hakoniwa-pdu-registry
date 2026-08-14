require_relative 'pdu_type_HakoHilStateQuaternion'


module HakoPdu::HakoMavlinkMsgs::HakoHilStateQuaternionConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_hako_hil_state_quaternion(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoMavlinkMsgs::HakoHilStateQuaternion.new
    binary_read_recursive_hako_hil_state_quaternion(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_hako_hil_state_quaternion(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_hako_hil_state_quaternion(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_hako_hil_state_quaternion(meta, binary_data, obj, base_off)
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    obj.time_usec = read_primitive('uint64', binary_data.byteslice(base_off + 0, 8))

    # member: attitude_quaternion, type: float32 (primitive), offset: 8, size: 16
    obj.attitude_quaternion = read_primitive_array('float32', binary_data.byteslice(base_off + 8, 16), 4, 16 / 4)

    # member: rollspeed, type: float32 (primitive), offset: 24, size: 4
    obj.rollspeed = read_primitive('float32', binary_data.byteslice(base_off + 24, 4))

    # member: pitchspeed, type: float32 (primitive), offset: 28, size: 4
    obj.pitchspeed = read_primitive('float32', binary_data.byteslice(base_off + 28, 4))

    # member: yawspeed, type: float32 (primitive), offset: 32, size: 4
    obj.yawspeed = read_primitive('float32', binary_data.byteslice(base_off + 32, 4))

    # member: lat, type: int32 (primitive), offset: 36, size: 4
    obj.lat = read_primitive('int32', binary_data.byteslice(base_off + 36, 4))

    # member: lon, type: int32 (primitive), offset: 40, size: 4
    obj.lon = read_primitive('int32', binary_data.byteslice(base_off + 40, 4))

    # member: alt, type: int32 (primitive), offset: 44, size: 4
    obj.alt = read_primitive('int32', binary_data.byteslice(base_off + 44, 4))

    # member: vx, type: int16 (primitive), offset: 48, size: 2
    obj.vx = read_primitive('int16', binary_data.byteslice(base_off + 48, 2))

    # member: vy, type: int16 (primitive), offset: 50, size: 2
    obj.vy = read_primitive('int16', binary_data.byteslice(base_off + 50, 2))

    # member: vz, type: int16 (primitive), offset: 52, size: 2
    obj.vz = read_primitive('int16', binary_data.byteslice(base_off + 52, 2))

    # member: ind_airspeed, type: uint16 (primitive), offset: 54, size: 2
    obj.ind_airspeed = read_primitive('uint16', binary_data.byteslice(base_off + 54, 2))

    # member: true_airspeed, type: uint16 (primitive), offset: 56, size: 2
    obj.true_airspeed = read_primitive('uint16', binary_data.byteslice(base_off + 56, 2))

    # member: xacc, type: int16 (primitive), offset: 58, size: 2
    obj.xacc = read_primitive('int16', binary_data.byteslice(base_off + 58, 2))

    # member: yacc, type: int16 (primitive), offset: 60, size: 2
    obj.yacc = read_primitive('int16', binary_data.byteslice(base_off + 60, 2))

    # member: zacc, type: int16 (primitive), offset: 62, size: 2
    obj.zacc = read_primitive('int16', binary_data.byteslice(base_off + 62, 2))

    obj
  end

  def self.binary_write_recursive_hako_hil_state_quaternion(parent_off, heap_data, allocator, obj)
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    add_binary(allocator, parent_off + 0, primitive_to_bin('uint64', obj.time_usec, 8))

    # member: attitude_quaternion, type: float32 (primitive), offset: 8, size: 16
    add_binary(allocator, parent_off + 8, primitive_array_to_bin('float32', obj.attitude_quaternion, 16 / 4))

    # member: rollspeed, type: float32 (primitive), offset: 24, size: 4
    add_binary(allocator, parent_off + 24, primitive_to_bin('float32', obj.rollspeed, 4))

    # member: pitchspeed, type: float32 (primitive), offset: 28, size: 4
    add_binary(allocator, parent_off + 28, primitive_to_bin('float32', obj.pitchspeed, 4))

    # member: yawspeed, type: float32 (primitive), offset: 32, size: 4
    add_binary(allocator, parent_off + 32, primitive_to_bin('float32', obj.yawspeed, 4))

    # member: lat, type: int32 (primitive), offset: 36, size: 4
    add_binary(allocator, parent_off + 36, primitive_to_bin('int32', obj.lat, 4))

    # member: lon, type: int32 (primitive), offset: 40, size: 4
    add_binary(allocator, parent_off + 40, primitive_to_bin('int32', obj.lon, 4))

    # member: alt, type: int32 (primitive), offset: 44, size: 4
    add_binary(allocator, parent_off + 44, primitive_to_bin('int32', obj.alt, 4))

    # member: vx, type: int16 (primitive), offset: 48, size: 2
    add_binary(allocator, parent_off + 48, primitive_to_bin('int16', obj.vx, 2))

    # member: vy, type: int16 (primitive), offset: 50, size: 2
    add_binary(allocator, parent_off + 50, primitive_to_bin('int16', obj.vy, 2))

    # member: vz, type: int16 (primitive), offset: 52, size: 2
    add_binary(allocator, parent_off + 52, primitive_to_bin('int16', obj.vz, 2))

    # member: ind_airspeed, type: uint16 (primitive), offset: 54, size: 2
    add_binary(allocator, parent_off + 54, primitive_to_bin('uint16', obj.ind_airspeed, 2))

    # member: true_airspeed, type: uint16 (primitive), offset: 56, size: 2
    add_binary(allocator, parent_off + 56, primitive_to_bin('uint16', obj.true_airspeed, 2))

    # member: xacc, type: int16 (primitive), offset: 58, size: 2
    add_binary(allocator, parent_off + 58, primitive_to_bin('int16', obj.xacc, 2))

    # member: yacc, type: int16 (primitive), offset: 60, size: 2
    add_binary(allocator, parent_off + 60, primitive_to_bin('int16', obj.yacc, 2))

    # member: zacc, type: int16 (primitive), offset: 62, size: 2
    add_binary(allocator, parent_off + 62, primitive_to_bin('int16', obj.zacc, 2))

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
