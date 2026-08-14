require_relative 'pdu_type_Ev3PduSensor'
require_relative 'pdu_type_Ev3PduSensorHeader'
require_relative 'pdu_conv_Ev3PduSensorHeader'
require_relative 'pdu_type_Ev3PduColorSensor'
require_relative 'pdu_conv_Ev3PduColorSensor'
require_relative 'pdu_type_Ev3PduTouchSensor'
require_relative 'pdu_conv_Ev3PduTouchSensor'


module HakoPdu::Ev3Msgs::Ev3PduSensorConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_ev3_pdu_sensor(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::Ev3Msgs::Ev3PduSensor.new
    binary_read_recursive_ev3_pdu_sensor(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_ev3_pdu_sensor(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_ev3_pdu_sensor(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_ev3_pdu_sensor(meta, binary_data, obj, base_off)
    # member: head, type: Ev3PduSensorHeader (struct), offset: 0, size: 152
    obj.head = HakoPdu::Ev3Msgs::Ev3PduSensorHeader.new
    HakoPdu::Ev3Msgs::Ev3PduSensorHeaderConverter.binary_read_recursive_ev3_pdu_sensor_header(meta, binary_data, obj.head, base_off + 0)

    # member: buttons, type: uint8 (primitive), offset: 152, size: 1
    obj.buttons = read_primitive_array('uint8', binary_data.byteslice(base_off + 152, 1), 1, 1 / 1)

    # member: color_sensors, type: Ev3PduColorSensor (struct), offset: 156, size: 40
    obj.color_sensors = []
    2.times do |i|
      child = HakoPdu::Ev3Msgs::Ev3PduColorSensor.new
      HakoPdu::Ev3Msgs::Ev3PduColorSensorConverter.binary_read_recursive_ev3_pdu_color_sensor(meta, binary_data, child, base_off + 156 + i * (40 / 2))
      obj.color_sensors << child
    end

    # member: touch_sensors, type: Ev3PduTouchSensor (struct), offset: 196, size: 8
    obj.touch_sensors = []
    2.times do |i|
      child = HakoPdu::Ev3Msgs::Ev3PduTouchSensor.new
      HakoPdu::Ev3Msgs::Ev3PduTouchSensorConverter.binary_read_recursive_ev3_pdu_touch_sensor(meta, binary_data, child, base_off + 196 + i * (8 / 2))
      obj.touch_sensors << child
    end

    # member: motor_angle, type: uint32 (primitive), offset: 204, size: 12
    obj.motor_angle = read_primitive_array('uint32', binary_data.byteslice(base_off + 204, 12), 3, 12 / 3)

    # member: gyro_degree, type: int32 (primitive), offset: 216, size: 4
    obj.gyro_degree = read_primitive('int32', binary_data.byteslice(base_off + 216, 4))

    # member: gyro_degree_rate, type: int32 (primitive), offset: 220, size: 4
    obj.gyro_degree_rate = read_primitive('int32', binary_data.byteslice(base_off + 220, 4))

    # member: sensor_ultrasonic, type: uint32 (primitive), offset: 224, size: 4
    obj.sensor_ultrasonic = read_primitive('uint32', binary_data.byteslice(base_off + 224, 4))

    # member: gps_lat, type: float64 (primitive), offset: 232, size: 8
    obj.gps_lat = read_primitive('float64', binary_data.byteslice(base_off + 232, 8))

    # member: gps_lon, type: float64 (primitive), offset: 240, size: 8
    obj.gps_lon = read_primitive('float64', binary_data.byteslice(base_off + 240, 8))

    obj
  end

  def self.binary_write_recursive_ev3_pdu_sensor(parent_off, heap_data, allocator, obj)
    # member: head, type: Ev3PduSensorHeader (struct), offset: 0, size: 152
    HakoPdu::Ev3Msgs::Ev3PduSensorHeaderConverter.binary_write_recursive_ev3_pdu_sensor_header(parent_off + 0, heap_data, allocator, obj.head)

    # member: buttons, type: uint8 (primitive), offset: 152, size: 1
    add_binary(allocator, parent_off + 152, primitive_array_to_bin('uint8', obj.buttons, 1 / 1))

    # member: color_sensors, type: Ev3PduColorSensor (struct), offset: 156, size: 40
    (obj.color_sensors || []).each_with_index do |child, i|
      HakoPdu::Ev3Msgs::Ev3PduColorSensorConverter.binary_write_recursive_ev3_pdu_color_sensor(parent_off + 156 + i * (40 / 2), heap_data, allocator, child)
    end

    # member: touch_sensors, type: Ev3PduTouchSensor (struct), offset: 196, size: 8
    (obj.touch_sensors || []).each_with_index do |child, i|
      HakoPdu::Ev3Msgs::Ev3PduTouchSensorConverter.binary_write_recursive_ev3_pdu_touch_sensor(parent_off + 196 + i * (8 / 2), heap_data, allocator, child)
    end

    # member: motor_angle, type: uint32 (primitive), offset: 204, size: 12
    add_binary(allocator, parent_off + 204, primitive_array_to_bin('uint32', obj.motor_angle, 12 / 3))

    # member: gyro_degree, type: int32 (primitive), offset: 216, size: 4
    add_binary(allocator, parent_off + 216, primitive_to_bin('int32', obj.gyro_degree, 4))

    # member: gyro_degree_rate, type: int32 (primitive), offset: 220, size: 4
    add_binary(allocator, parent_off + 220, primitive_to_bin('int32', obj.gyro_degree_rate, 4))

    # member: sensor_ultrasonic, type: uint32 (primitive), offset: 224, size: 4
    add_binary(allocator, parent_off + 224, primitive_to_bin('uint32', obj.sensor_ultrasonic, 4))

    # member: gps_lat, type: float64 (primitive), offset: 232, size: 8
    add_binary(allocator, parent_off + 232, primitive_to_bin('float64', obj.gps_lat, 8))

    # member: gps_lon, type: float64 (primitive), offset: 240, size: 8
    add_binary(allocator, parent_off + 240, primitive_to_bin('float64', obj.gps_lon, 8))

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
