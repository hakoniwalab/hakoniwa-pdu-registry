require_relative 'pdu_type_Range'
require_relative '../std_msgs/pdu_type_Header'
require_relative '../std_msgs/pdu_conv_Header'


module HakoPdu::SensorMsgs::RangeConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_range(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::SensorMsgs::Range.new
    binary_read_recursive_range(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_range(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_range(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_range(meta, binary_data, obj, base_off)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    obj.header = HakoPdu::StdMsgs::Header.new
    HakoPdu::StdMsgs::HeaderConverter.binary_read_recursive_header(meta, binary_data, obj.header, base_off + 0)

    # member: radiation_type, type: uint8 (primitive), offset: 136, size: 1
    obj.radiation_type = read_primitive('uint8', binary_data.byteslice(base_off + 136, 1))

    # member: field_of_view, type: float32 (primitive), offset: 140, size: 4
    obj.field_of_view = read_primitive('float32', binary_data.byteslice(base_off + 140, 4))

    # member: min_range, type: float32 (primitive), offset: 144, size: 4
    obj.min_range = read_primitive('float32', binary_data.byteslice(base_off + 144, 4))

    # member: max_range, type: float32 (primitive), offset: 148, size: 4
    obj.max_range = read_primitive('float32', binary_data.byteslice(base_off + 148, 4))

    # member: range, type: float32 (primitive), offset: 152, size: 4
    obj.range = read_primitive('float32', binary_data.byteslice(base_off + 152, 4))

    # member: variance, type: float32 (primitive), offset: 156, size: 4
    obj.variance = read_primitive('float32', binary_data.byteslice(base_off + 156, 4))

    obj
  end

  def self.binary_write_recursive_range(parent_off, heap_data, allocator, obj)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    HakoPdu::StdMsgs::HeaderConverter.binary_write_recursive_header(parent_off + 0, heap_data, allocator, obj.header)

    # member: radiation_type, type: uint8 (primitive), offset: 136, size: 1
    add_binary(allocator, parent_off + 136, primitive_to_bin('uint8', obj.radiation_type, 1))

    # member: field_of_view, type: float32 (primitive), offset: 140, size: 4
    add_binary(allocator, parent_off + 140, primitive_to_bin('float32', obj.field_of_view, 4))

    # member: min_range, type: float32 (primitive), offset: 144, size: 4
    add_binary(allocator, parent_off + 144, primitive_to_bin('float32', obj.min_range, 4))

    # member: max_range, type: float32 (primitive), offset: 148, size: 4
    add_binary(allocator, parent_off + 148, primitive_to_bin('float32', obj.max_range, 4))

    # member: range, type: float32 (primitive), offset: 152, size: 4
    add_binary(allocator, parent_off + 152, primitive_to_bin('float32', obj.range, 4))

    # member: variance, type: float32 (primitive), offset: 156, size: 4
    add_binary(allocator, parent_off + 156, primitive_to_bin('float32', obj.variance, 4))

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
