require_relative 'pdu_type_RenderCameraFrameResponse'
require_relative '../sensor_msgs/pdu_type_Image'
require_relative '../sensor_msgs/pdu_conv_Image'


module HakoPdu::HakoSrvMsgs::RenderCameraFrameResponseConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_render_camera_frame_response(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoSrvMsgs::RenderCameraFrameResponse.new
    binary_read_recursive_render_camera_frame_response(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_render_camera_frame_response(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_render_camera_frame_response(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_render_camera_frame_response(meta, binary_data, obj, base_off)
    # member: result_code, type: uint32 (primitive), offset: 0, size: 4
    obj.result_code = read_primitive('uint32', binary_data.byteslice(base_off + 0, 4))

    # member: sim_time_usec, type: uint64 (primitive), offset: 8, size: 8
    obj.sim_time_usec = read_primitive('uint64', binary_data.byteslice(base_off + 8, 8))

    # member: rgb, type: sensor_msgs/Image (struct), offset: 16, size: 288
    obj.rgb = HakoPdu::SensorMsgs::Image.new
    HakoPdu::SensorMsgs::ImageConverter.binary_read_recursive_image(meta, binary_data, obj.rgb, base_off + 16)

    # member: depth, type: sensor_msgs/Image (struct), offset: 304, size: 288
    obj.depth = HakoPdu::SensorMsgs::Image.new
    HakoPdu::SensorMsgs::ImageConverter.binary_read_recursive_image(meta, binary_data, obj.depth, base_off + 304)

    # member: segmentation, type: sensor_msgs/Image (struct), offset: 592, size: 288
    obj.segmentation = HakoPdu::SensorMsgs::Image.new
    HakoPdu::SensorMsgs::ImageConverter.binary_read_recursive_image(meta, binary_data, obj.segmentation, base_off + 592)

    obj
  end

  def self.binary_write_recursive_render_camera_frame_response(parent_off, heap_data, allocator, obj)
    # member: result_code, type: uint32 (primitive), offset: 0, size: 4
    add_binary(allocator, parent_off + 0, primitive_to_bin('uint32', obj.result_code, 4))

    # member: sim_time_usec, type: uint64 (primitive), offset: 8, size: 8
    add_binary(allocator, parent_off + 8, primitive_to_bin('uint64', obj.sim_time_usec, 8))

    # member: rgb, type: sensor_msgs/Image (struct), offset: 16, size: 288
    HakoPdu::SensorMsgs::ImageConverter.binary_write_recursive_image(parent_off + 16, heap_data, allocator, obj.rgb)

    # member: depth, type: sensor_msgs/Image (struct), offset: 304, size: 288
    HakoPdu::SensorMsgs::ImageConverter.binary_write_recursive_image(parent_off + 304, heap_data, allocator, obj.depth)

    # member: segmentation, type: sensor_msgs/Image (struct), offset: 592, size: 288
    HakoPdu::SensorMsgs::ImageConverter.binary_write_recursive_image(parent_off + 592, heap_data, allocator, obj.segmentation)

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
