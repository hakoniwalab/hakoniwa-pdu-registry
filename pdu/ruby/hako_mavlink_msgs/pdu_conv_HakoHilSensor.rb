require_relative 'pdu_type_HakoHilSensor'


module HakoPdu::HakoMavlinkMsgs::HakoHilSensorConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_hako_hil_sensor(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoMavlinkMsgs::HakoHilSensor.new
    binary_read_recursive_hako_hil_sensor(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_hako_hil_sensor(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_hako_hil_sensor(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_hako_hil_sensor(meta, binary_data, obj, base_off)
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    obj.time_usec = read_primitive('uint64', binary_data.byteslice(base_off + 0, 8))

    # member: xacc, type: float32 (primitive), offset: 8, size: 4
    obj.xacc = read_primitive('float32', binary_data.byteslice(base_off + 8, 4))

    # member: yacc, type: float32 (primitive), offset: 12, size: 4
    obj.yacc = read_primitive('float32', binary_data.byteslice(base_off + 12, 4))

    # member: zacc, type: float32 (primitive), offset: 16, size: 4
    obj.zacc = read_primitive('float32', binary_data.byteslice(base_off + 16, 4))

    # member: xgyro, type: float32 (primitive), offset: 20, size: 4
    obj.xgyro = read_primitive('float32', binary_data.byteslice(base_off + 20, 4))

    # member: ygyro, type: float32 (primitive), offset: 24, size: 4
    obj.ygyro = read_primitive('float32', binary_data.byteslice(base_off + 24, 4))

    # member: zgyro, type: float32 (primitive), offset: 28, size: 4
    obj.zgyro = read_primitive('float32', binary_data.byteslice(base_off + 28, 4))

    # member: xmag, type: float32 (primitive), offset: 32, size: 4
    obj.xmag = read_primitive('float32', binary_data.byteslice(base_off + 32, 4))

    # member: ymag, type: float32 (primitive), offset: 36, size: 4
    obj.ymag = read_primitive('float32', binary_data.byteslice(base_off + 36, 4))

    # member: zmag, type: float32 (primitive), offset: 40, size: 4
    obj.zmag = read_primitive('float32', binary_data.byteslice(base_off + 40, 4))

    # member: abs_pressure, type: float32 (primitive), offset: 44, size: 4
    obj.abs_pressure = read_primitive('float32', binary_data.byteslice(base_off + 44, 4))

    # member: diff_pressure, type: float32 (primitive), offset: 48, size: 4
    obj.diff_pressure = read_primitive('float32', binary_data.byteslice(base_off + 48, 4))

    # member: pressure_alt, type: float32 (primitive), offset: 52, size: 4
    obj.pressure_alt = read_primitive('float32', binary_data.byteslice(base_off + 52, 4))

    # member: temperature, type: float32 (primitive), offset: 56, size: 4
    obj.temperature = read_primitive('float32', binary_data.byteslice(base_off + 56, 4))

    # member: fields_updated, type: uint32 (primitive), offset: 60, size: 4
    obj.fields_updated = read_primitive('uint32', binary_data.byteslice(base_off + 60, 4))

    # member: id, type: uint8 (primitive), offset: 64, size: 1
    obj.id = read_primitive('uint8', binary_data.byteslice(base_off + 64, 1))

    obj
  end

  def self.binary_write_recursive_hako_hil_sensor(parent_off, heap_data, allocator, obj)
    # member: time_usec, type: uint64 (primitive), offset: 0, size: 8
    add_binary(allocator, parent_off + 0, primitive_to_bin('uint64', obj.time_usec, 8))

    # member: xacc, type: float32 (primitive), offset: 8, size: 4
    add_binary(allocator, parent_off + 8, primitive_to_bin('float32', obj.xacc, 4))

    # member: yacc, type: float32 (primitive), offset: 12, size: 4
    add_binary(allocator, parent_off + 12, primitive_to_bin('float32', obj.yacc, 4))

    # member: zacc, type: float32 (primitive), offset: 16, size: 4
    add_binary(allocator, parent_off + 16, primitive_to_bin('float32', obj.zacc, 4))

    # member: xgyro, type: float32 (primitive), offset: 20, size: 4
    add_binary(allocator, parent_off + 20, primitive_to_bin('float32', obj.xgyro, 4))

    # member: ygyro, type: float32 (primitive), offset: 24, size: 4
    add_binary(allocator, parent_off + 24, primitive_to_bin('float32', obj.ygyro, 4))

    # member: zgyro, type: float32 (primitive), offset: 28, size: 4
    add_binary(allocator, parent_off + 28, primitive_to_bin('float32', obj.zgyro, 4))

    # member: xmag, type: float32 (primitive), offset: 32, size: 4
    add_binary(allocator, parent_off + 32, primitive_to_bin('float32', obj.xmag, 4))

    # member: ymag, type: float32 (primitive), offset: 36, size: 4
    add_binary(allocator, parent_off + 36, primitive_to_bin('float32', obj.ymag, 4))

    # member: zmag, type: float32 (primitive), offset: 40, size: 4
    add_binary(allocator, parent_off + 40, primitive_to_bin('float32', obj.zmag, 4))

    # member: abs_pressure, type: float32 (primitive), offset: 44, size: 4
    add_binary(allocator, parent_off + 44, primitive_to_bin('float32', obj.abs_pressure, 4))

    # member: diff_pressure, type: float32 (primitive), offset: 48, size: 4
    add_binary(allocator, parent_off + 48, primitive_to_bin('float32', obj.diff_pressure, 4))

    # member: pressure_alt, type: float32 (primitive), offset: 52, size: 4
    add_binary(allocator, parent_off + 52, primitive_to_bin('float32', obj.pressure_alt, 4))

    # member: temperature, type: float32 (primitive), offset: 56, size: 4
    add_binary(allocator, parent_off + 56, primitive_to_bin('float32', obj.temperature, 4))

    # member: fields_updated, type: uint32 (primitive), offset: 60, size: 4
    add_binary(allocator, parent_off + 60, primitive_to_bin('uint32', obj.fields_updated, 4))

    # member: id, type: uint8 (primitive), offset: 64, size: 1
    add_binary(allocator, parent_off + 64, primitive_to_bin('uint8', obj.id, 1))

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
