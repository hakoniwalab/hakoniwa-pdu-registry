require_relative 'pdu_type_Inertia'
require_relative 'pdu_type_Vector3'
require_relative 'pdu_conv_Vector3'


module HakoPdu::GeometryMsgs::InertiaConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_inertia(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::GeometryMsgs::Inertia.new
    binary_read_recursive_inertia(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_inertia(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_inertia(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_inertia(meta, binary_data, obj, base_off)
    # member: m, type: float64 (primitive), offset: 0, size: 8
    obj.m = read_primitive('float64', binary_data.byteslice(base_off + 0, 8))

    # member: com, type: geometry_msgs/Vector3 (struct), offset: 8, size: 24
    obj.com = HakoPdu::GeometryMsgs::Vector3.new
    HakoPdu::GeometryMsgs::Vector3Converter.binary_read_recursive_vector3(meta, binary_data, obj.com, base_off + 8)

    # member: ixx, type: float64 (primitive), offset: 32, size: 8
    obj.ixx = read_primitive('float64', binary_data.byteslice(base_off + 32, 8))

    # member: ixy, type: float64 (primitive), offset: 40, size: 8
    obj.ixy = read_primitive('float64', binary_data.byteslice(base_off + 40, 8))

    # member: ixz, type: float64 (primitive), offset: 48, size: 8
    obj.ixz = read_primitive('float64', binary_data.byteslice(base_off + 48, 8))

    # member: iyy, type: float64 (primitive), offset: 56, size: 8
    obj.iyy = read_primitive('float64', binary_data.byteslice(base_off + 56, 8))

    # member: iyz, type: float64 (primitive), offset: 64, size: 8
    obj.iyz = read_primitive('float64', binary_data.byteslice(base_off + 64, 8))

    # member: izz, type: float64 (primitive), offset: 72, size: 8
    obj.izz = read_primitive('float64', binary_data.byteslice(base_off + 72, 8))

    obj
  end

  def self.binary_write_recursive_inertia(parent_off, heap_data, allocator, obj)
    # member: m, type: float64 (primitive), offset: 0, size: 8
    add_binary(allocator, parent_off + 0, primitive_to_bin('float64', obj.m, 8))

    # member: com, type: geometry_msgs/Vector3 (struct), offset: 8, size: 24
    HakoPdu::GeometryMsgs::Vector3Converter.binary_write_recursive_vector3(parent_off + 8, heap_data, allocator, obj.com)

    # member: ixx, type: float64 (primitive), offset: 32, size: 8
    add_binary(allocator, parent_off + 32, primitive_to_bin('float64', obj.ixx, 8))

    # member: ixy, type: float64 (primitive), offset: 40, size: 8
    add_binary(allocator, parent_off + 40, primitive_to_bin('float64', obj.ixy, 8))

    # member: ixz, type: float64 (primitive), offset: 48, size: 8
    add_binary(allocator, parent_off + 48, primitive_to_bin('float64', obj.ixz, 8))

    # member: iyy, type: float64 (primitive), offset: 56, size: 8
    add_binary(allocator, parent_off + 56, primitive_to_bin('float64', obj.iyy, 8))

    # member: iyz, type: float64 (primitive), offset: 64, size: 8
    add_binary(allocator, parent_off + 64, primitive_to_bin('float64', obj.iyz, 8))

    # member: izz, type: float64 (primitive), offset: 72, size: 8
    add_binary(allocator, parent_off + 72, primitive_to_bin('float64', obj.izz, 8))

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
