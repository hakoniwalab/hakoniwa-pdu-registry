require_relative 'pdu_type_Disturbance'
require_relative 'pdu_type_DisturbanceTemperature'
require_relative 'pdu_conv_DisturbanceTemperature'
require_relative 'pdu_type_DisturbanceWind'
require_relative 'pdu_conv_DisturbanceWind'
require_relative 'pdu_type_DisturbanceAtm'
require_relative 'pdu_conv_DisturbanceAtm'
require_relative 'pdu_type_DisturbanceBoundary'
require_relative 'pdu_conv_DisturbanceBoundary'
require_relative 'pdu_type_DisturbanceUserCustom'
require_relative 'pdu_conv_DisturbanceUserCustom'


module HakoPdu::HakoMsgs::DisturbanceConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_disturbance(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::HakoMsgs::Disturbance.new
    binary_read_recursive_disturbance(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_disturbance(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_disturbance(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_disturbance(meta, binary_data, obj, base_off)
    # member: d_temp, type: hako_msgs/DisturbanceTemperature (struct), offset: 0, size: 8
    obj.d_temp = HakoPdu::HakoMsgs::DisturbanceTemperature.new
    HakoPdu::HakoMsgs::DisturbanceTemperatureConverter.binary_read_recursive_disturbance_temperature(meta, binary_data, obj.d_temp, base_off + 0)

    # member: d_wind, type: hako_msgs/DisturbanceWind (struct), offset: 8, size: 24
    obj.d_wind = HakoPdu::HakoMsgs::DisturbanceWind.new
    HakoPdu::HakoMsgs::DisturbanceWindConverter.binary_read_recursive_disturbance_wind(meta, binary_data, obj.d_wind, base_off + 8)

    # member: d_atm, type: hako_msgs/DisturbanceAtm (struct), offset: 32, size: 8
    obj.d_atm = HakoPdu::HakoMsgs::DisturbanceAtm.new
    HakoPdu::HakoMsgs::DisturbanceAtmConverter.binary_read_recursive_disturbance_atm(meta, binary_data, obj.d_atm, base_off + 32)

    # member: d_boundary, type: hako_msgs/DisturbanceBoundary (struct), offset: 40, size: 48
    obj.d_boundary = HakoPdu::HakoMsgs::DisturbanceBoundary.new
    HakoPdu::HakoMsgs::DisturbanceBoundaryConverter.binary_read_recursive_disturbance_boundary(meta, binary_data, obj.d_boundary, base_off + 40)

    # member: d_user_custom, type: hako_msgs/DisturbanceUserCustom (struct), offset: 88, size: 8
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 88, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 88 + 4, 4))
    obj.d_user_custom = []
    array_size.times do |i|
      child = HakoPdu::HakoMsgs::DisturbanceUserCustom.new
      HakoPdu::HakoMsgs::DisturbanceUserCustomConverter.binary_read_recursive_disturbance_user_custom(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 8)
      obj.d_user_custom << child
    end

    obj
  end

  def self.binary_write_recursive_disturbance(parent_off, heap_data, allocator, obj)
    # member: d_temp, type: hako_msgs/DisturbanceTemperature (struct), offset: 0, size: 8
    HakoPdu::HakoMsgs::DisturbanceTemperatureConverter.binary_write_recursive_disturbance_temperature(parent_off + 0, heap_data, allocator, obj.d_temp)

    # member: d_wind, type: hako_msgs/DisturbanceWind (struct), offset: 8, size: 24
    HakoPdu::HakoMsgs::DisturbanceWindConverter.binary_write_recursive_disturbance_wind(parent_off + 8, heap_data, allocator, obj.d_wind)

    # member: d_atm, type: hako_msgs/DisturbanceAtm (struct), offset: 32, size: 8
    HakoPdu::HakoMsgs::DisturbanceAtmConverter.binary_write_recursive_disturbance_atm(parent_off + 32, heap_data, allocator, obj.d_atm)

    # member: d_boundary, type: hako_msgs/DisturbanceBoundary (struct), offset: 40, size: 48
    HakoPdu::HakoMsgs::DisturbanceBoundaryConverter.binary_write_recursive_disturbance_boundary(parent_off + 40, heap_data, allocator, obj.d_boundary)

    # member: d_user_custom, type: hako_msgs/DisturbanceUserCustom (struct), offset: 88, size: 8
    offset_from_heap = heap_data.bytesize
    values = obj.d_user_custom || []
    add_binary(allocator, parent_off + 88, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 8))
    values.each_with_index do |child, i|
      HakoPdu::HakoMsgs::DisturbanceUserCustomConverter.binary_write_recursive_disturbance_user_custom(offset_from_heap + i * 8, heap_data, heap_data, child)
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
