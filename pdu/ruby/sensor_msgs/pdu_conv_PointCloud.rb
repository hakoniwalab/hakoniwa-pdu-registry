require_relative 'pdu_type_PointCloud'
require_relative '../std_msgs/pdu_type_Header'
require_relative '../std_msgs/pdu_conv_Header'
require_relative '../geometry_msgs/pdu_type_Point32'
require_relative '../geometry_msgs/pdu_conv_Point32'
require_relative 'pdu_type_ChannelFloat32'
require_relative 'pdu_conv_ChannelFloat32'


module HakoPdu::SensorMsgs::PointCloudConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_point_cloud(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::SensorMsgs::PointCloud.new
    binary_read_recursive_point_cloud(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_point_cloud(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_point_cloud(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_point_cloud(meta, binary_data, obj, base_off)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    obj.header = HakoPdu::StdMsgs::Header.new
    HakoPdu::StdMsgs::HeaderConverter.binary_read_recursive_header(meta, binary_data, obj.header, base_off + 0)

    # member: points, type: geometry_msgs/Point32 (struct), offset: 136, size: 12
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 136, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 136 + 4, 4))
    obj.points = []
    array_size.times do |i|
      child = HakoPdu::GeometryMsgs::Point32.new
      HakoPdu::GeometryMsgs::Point32Converter.binary_read_recursive_point32(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 12)
      obj.points << child
    end

    # member: channels, type: ChannelFloat32 (struct), offset: 144, size: 136
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 144, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 144 + 4, 4))
    obj.channels = []
    array_size.times do |i|
      child = HakoPdu::SensorMsgs::ChannelFloat32.new
      HakoPdu::SensorMsgs::ChannelFloat32Converter.binary_read_recursive_channel_float32(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 136)
      obj.channels << child
    end

    obj
  end

  def self.binary_write_recursive_point_cloud(parent_off, heap_data, allocator, obj)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    HakoPdu::StdMsgs::HeaderConverter.binary_write_recursive_header(parent_off + 0, heap_data, allocator, obj.header)

    # member: points, type: geometry_msgs/Point32 (struct), offset: 136, size: 12
    offset_from_heap = heap_data.bytesize
    values = obj.points || []
    add_binary(allocator, parent_off + 136, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 12))
    values.each_with_index do |child, i|
      HakoPdu::GeometryMsgs::Point32Converter.binary_write_recursive_point32(offset_from_heap + i * 12, heap_data, heap_data, child)
    end

    # member: channels, type: ChannelFloat32 (struct), offset: 144, size: 136
    offset_from_heap = heap_data.bytesize
    values = obj.channels || []
    add_binary(allocator, parent_off + 144, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 136))
    values.each_with_index do |child, i|
      HakoPdu::SensorMsgs::ChannelFloat32Converter.binary_write_recursive_channel_float32(offset_from_heap + i * 136, heap_data, heap_data, child)
    end

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
