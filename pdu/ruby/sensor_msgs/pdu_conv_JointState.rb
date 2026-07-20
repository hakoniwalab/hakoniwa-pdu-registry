require_relative 'pdu_type_JointState'
require_relative '../std_msgs/pdu_type_Header'
require_relative '../std_msgs/pdu_conv_Header'


module HakoPdu::SensorMsgs::JointStateConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_joint_state(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::SensorMsgs::JointState.new
    binary_read_recursive_joint_state(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_joint_state(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_joint_state(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_joint_state(meta, binary_data, obj, base_off)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    obj.header = HakoPdu::StdMsgs::Header.new
    HakoPdu::StdMsgs::HeaderConverter.binary_read_recursive_header(meta, binary_data, obj.header, base_off + 0)

    # member: name, type: string (primitive), offset: 136, size: 128
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 136, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 136 + 4, 4))
    obj.name = read_primitive_array('string', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 128 * array_size), array_size, 128)

    # member: position, type: float64 (primitive), offset: 144, size: 8
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 144, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 144 + 4, 4))
    obj.position = read_primitive_array('float64', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 8 * array_size), array_size, 8)

    # member: velocity, type: float64 (primitive), offset: 152, size: 8
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 152, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 152 + 4, 4))
    obj.velocity = read_primitive_array('float64', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 8 * array_size), array_size, 8)

    # member: effort, type: float64 (primitive), offset: 160, size: 8
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 160, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 160 + 4, 4))
    obj.effort = read_primitive_array('float64', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 8 * array_size), array_size, 8)

    obj
  end

  def self.binary_write_recursive_joint_state(parent_off, heap_data, allocator, obj)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    HakoPdu::StdMsgs::HeaderConverter.binary_write_recursive_header(parent_off + 0, heap_data, allocator, obj.header)

    # member: name, type: string (primitive), offset: 136, size: 128
    offset_from_heap = heap_data.bytesize
    values = obj.name || []
    add_binary(allocator, parent_off + 136, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('string', values, 128))

    # member: position, type: float64 (primitive), offset: 144, size: 8
    offset_from_heap = heap_data.bytesize
    values = obj.position || []
    add_binary(allocator, parent_off + 144, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('float64', values, 8))

    # member: velocity, type: float64 (primitive), offset: 152, size: 8
    offset_from_heap = heap_data.bytesize
    values = obj.velocity || []
    add_binary(allocator, parent_off + 152, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('float64', values, 8))

    # member: effort, type: float64 (primitive), offset: 160, size: 8
    offset_from_heap = heap_data.bytesize
    values = obj.effort || []
    add_binary(allocator, parent_off + 160, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('float64', values, 8))

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
