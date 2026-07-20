require_relative 'pdu_type_HakoSERVO_OUTPUT_RAW'


module HakoPdu::HakoMavlink2Msgs::HakoSERVO_OUTPUT_RAWConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoMavlink2Msgs::HakoSERVO_OUTPUT_RAW.new
    binary_read_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(meta, binary_data, obj, base_off)
    # member: time_usec, type: uint32 (primitive), offset: 0, size: 4
    obj.time_usec = read_primitive('uint32', binary_data.byteslice(base_off + 0, 4))

    # member: port, type: uint8 (primitive), offset: 4, size: 1
    obj.port = read_primitive('uint8', binary_data.byteslice(base_off + 4, 1))

    # member: servo1_raw, type: uint16 (primitive), offset: 6, size: 2
    obj.servo1_raw = read_primitive('uint16', binary_data.byteslice(base_off + 6, 2))

    # member: servo2_raw, type: uint16 (primitive), offset: 8, size: 2
    obj.servo2_raw = read_primitive('uint16', binary_data.byteslice(base_off + 8, 2))

    # member: servo3_raw, type: uint16 (primitive), offset: 10, size: 2
    obj.servo3_raw = read_primitive('uint16', binary_data.byteslice(base_off + 10, 2))

    # member: servo4_raw, type: uint16 (primitive), offset: 12, size: 2
    obj.servo4_raw = read_primitive('uint16', binary_data.byteslice(base_off + 12, 2))

    # member: servo5_raw, type: uint16 (primitive), offset: 14, size: 2
    obj.servo5_raw = read_primitive('uint16', binary_data.byteslice(base_off + 14, 2))

    # member: servo6_raw, type: uint16 (primitive), offset: 16, size: 2
    obj.servo6_raw = read_primitive('uint16', binary_data.byteslice(base_off + 16, 2))

    # member: servo7_raw, type: uint16 (primitive), offset: 18, size: 2
    obj.servo7_raw = read_primitive('uint16', binary_data.byteslice(base_off + 18, 2))

    # member: servo8_raw, type: uint16 (primitive), offset: 20, size: 2
    obj.servo8_raw = read_primitive('uint16', binary_data.byteslice(base_off + 20, 2))

    # member: servo9_raw, type: uint16 (primitive), offset: 22, size: 2
    obj.servo9_raw = read_primitive('uint16', binary_data.byteslice(base_off + 22, 2))

    # member: servo10_raw, type: uint16 (primitive), offset: 24, size: 2
    obj.servo10_raw = read_primitive('uint16', binary_data.byteslice(base_off + 24, 2))

    # member: servo11_raw, type: uint16 (primitive), offset: 26, size: 2
    obj.servo11_raw = read_primitive('uint16', binary_data.byteslice(base_off + 26, 2))

    # member: servo12_raw, type: uint16 (primitive), offset: 28, size: 2
    obj.servo12_raw = read_primitive('uint16', binary_data.byteslice(base_off + 28, 2))

    # member: servo13_raw, type: uint16 (primitive), offset: 30, size: 2
    obj.servo13_raw = read_primitive('uint16', binary_data.byteslice(base_off + 30, 2))

    # member: servo14_raw, type: uint16 (primitive), offset: 32, size: 2
    obj.servo14_raw = read_primitive('uint16', binary_data.byteslice(base_off + 32, 2))

    # member: servo15_raw, type: uint16 (primitive), offset: 34, size: 2
    obj.servo15_raw = read_primitive('uint16', binary_data.byteslice(base_off + 34, 2))

    # member: servo16_raw, type: uint16 (primitive), offset: 36, size: 2
    obj.servo16_raw = read_primitive('uint16', binary_data.byteslice(base_off + 36, 2))

    obj
  end

  def self.binary_write_recursive_hako_s_e_r_v_o__o_u_t_p_u_t__r_a_w(parent_off, heap_data, allocator, obj)
    # member: time_usec, type: uint32 (primitive), offset: 0, size: 4
    add_binary(allocator, parent_off + 0, primitive_to_bin('uint32', obj.time_usec, 4))

    # member: port, type: uint8 (primitive), offset: 4, size: 1
    add_binary(allocator, parent_off + 4, primitive_to_bin('uint8', obj.port, 1))

    # member: servo1_raw, type: uint16 (primitive), offset: 6, size: 2
    add_binary(allocator, parent_off + 6, primitive_to_bin('uint16', obj.servo1_raw, 2))

    # member: servo2_raw, type: uint16 (primitive), offset: 8, size: 2
    add_binary(allocator, parent_off + 8, primitive_to_bin('uint16', obj.servo2_raw, 2))

    # member: servo3_raw, type: uint16 (primitive), offset: 10, size: 2
    add_binary(allocator, parent_off + 10, primitive_to_bin('uint16', obj.servo3_raw, 2))

    # member: servo4_raw, type: uint16 (primitive), offset: 12, size: 2
    add_binary(allocator, parent_off + 12, primitive_to_bin('uint16', obj.servo4_raw, 2))

    # member: servo5_raw, type: uint16 (primitive), offset: 14, size: 2
    add_binary(allocator, parent_off + 14, primitive_to_bin('uint16', obj.servo5_raw, 2))

    # member: servo6_raw, type: uint16 (primitive), offset: 16, size: 2
    add_binary(allocator, parent_off + 16, primitive_to_bin('uint16', obj.servo6_raw, 2))

    # member: servo7_raw, type: uint16 (primitive), offset: 18, size: 2
    add_binary(allocator, parent_off + 18, primitive_to_bin('uint16', obj.servo7_raw, 2))

    # member: servo8_raw, type: uint16 (primitive), offset: 20, size: 2
    add_binary(allocator, parent_off + 20, primitive_to_bin('uint16', obj.servo8_raw, 2))

    # member: servo9_raw, type: uint16 (primitive), offset: 22, size: 2
    add_binary(allocator, parent_off + 22, primitive_to_bin('uint16', obj.servo9_raw, 2))

    # member: servo10_raw, type: uint16 (primitive), offset: 24, size: 2
    add_binary(allocator, parent_off + 24, primitive_to_bin('uint16', obj.servo10_raw, 2))

    # member: servo11_raw, type: uint16 (primitive), offset: 26, size: 2
    add_binary(allocator, parent_off + 26, primitive_to_bin('uint16', obj.servo11_raw, 2))

    # member: servo12_raw, type: uint16 (primitive), offset: 28, size: 2
    add_binary(allocator, parent_off + 28, primitive_to_bin('uint16', obj.servo12_raw, 2))

    # member: servo13_raw, type: uint16 (primitive), offset: 30, size: 2
    add_binary(allocator, parent_off + 30, primitive_to_bin('uint16', obj.servo13_raw, 2))

    # member: servo14_raw, type: uint16 (primitive), offset: 32, size: 2
    add_binary(allocator, parent_off + 32, primitive_to_bin('uint16', obj.servo14_raw, 2))

    # member: servo15_raw, type: uint16 (primitive), offset: 34, size: 2
    add_binary(allocator, parent_off + 34, primitive_to_bin('uint16', obj.servo15_raw, 2))

    # member: servo16_raw, type: uint16 (primitive), offset: 36, size: 2
    add_binary(allocator, parent_off + 36, primitive_to_bin('uint16', obj.servo16_raw, 2))

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
