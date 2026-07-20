require_relative 'pdu_type_BatteryState'
require_relative '../std_msgs/pdu_type_Header'
require_relative '../std_msgs/pdu_conv_Header'


module HakoPdu::SensorMsgs::BatteryStateConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_battery_state(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::SensorMsgs::BatteryState.new
    binary_read_recursive_battery_state(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_battery_state(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_battery_state(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_battery_state(meta, binary_data, obj, base_off)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    obj.header = HakoPdu::StdMsgs::Header.new
    HakoPdu::StdMsgs::HeaderConverter.binary_read_recursive_header(meta, binary_data, obj.header, base_off + 0)

    # member: voltage, type: float32 (primitive), offset: 136, size: 4
    obj.voltage = read_primitive('float32', binary_data.byteslice(base_off + 136, 4))

    # member: temperature, type: float32 (primitive), offset: 140, size: 4
    obj.temperature = read_primitive('float32', binary_data.byteslice(base_off + 140, 4))

    # member: current, type: float32 (primitive), offset: 144, size: 4
    obj.current = read_primitive('float32', binary_data.byteslice(base_off + 144, 4))

    # member: charge, type: float32 (primitive), offset: 148, size: 4
    obj.charge = read_primitive('float32', binary_data.byteslice(base_off + 148, 4))

    # member: capacity, type: float32 (primitive), offset: 152, size: 4
    obj.capacity = read_primitive('float32', binary_data.byteslice(base_off + 152, 4))

    # member: design_capacity, type: float32 (primitive), offset: 156, size: 4
    obj.design_capacity = read_primitive('float32', binary_data.byteslice(base_off + 156, 4))

    # member: percentage, type: float32 (primitive), offset: 160, size: 4
    obj.percentage = read_primitive('float32', binary_data.byteslice(base_off + 160, 4))

    # member: power_supply_status, type: uint8 (primitive), offset: 164, size: 1
    obj.power_supply_status = read_primitive('uint8', binary_data.byteslice(base_off + 164, 1))

    # member: power_supply_health, type: uint8 (primitive), offset: 165, size: 1
    obj.power_supply_health = read_primitive('uint8', binary_data.byteslice(base_off + 165, 1))

    # member: power_supply_technology, type: uint8 (primitive), offset: 166, size: 1
    obj.power_supply_technology = read_primitive('uint8', binary_data.byteslice(base_off + 166, 1))

    # member: present, type: bool (primitive), offset: 168, size: 4
    obj.present = read_primitive('bool', binary_data.byteslice(base_off + 168, 4))

    # member: cell_voltage, type: float32 (primitive), offset: 172, size: 4
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 172, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 172 + 4, 4))
    obj.cell_voltage = read_primitive_array('float32', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 4 * array_size), array_size, 4)

    # member: cell_temperature, type: float32 (primitive), offset: 180, size: 4
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 180, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 180 + 4, 4))
    obj.cell_temperature = read_primitive_array('float32', binary_data.byteslice(meta[:heap_off] + offset_from_heap, 4 * array_size), array_size, 4)

    # member: location, type: string (primitive), offset: 188, size: 128
    obj.location = read_primitive('string', binary_data.byteslice(base_off + 188, 128))

    # member: serial_number, type: string (primitive), offset: 316, size: 128
    obj.serial_number = read_primitive('string', binary_data.byteslice(base_off + 316, 128))

    obj
  end

  def self.binary_write_recursive_battery_state(parent_off, heap_data, allocator, obj)
    # member: header, type: std_msgs/Header (struct), offset: 0, size: 136
    HakoPdu::StdMsgs::HeaderConverter.binary_write_recursive_header(parent_off + 0, heap_data, allocator, obj.header)

    # member: voltage, type: float32 (primitive), offset: 136, size: 4
    add_binary(allocator, parent_off + 136, primitive_to_bin('float32', obj.voltage, 4))

    # member: temperature, type: float32 (primitive), offset: 140, size: 4
    add_binary(allocator, parent_off + 140, primitive_to_bin('float32', obj.temperature, 4))

    # member: current, type: float32 (primitive), offset: 144, size: 4
    add_binary(allocator, parent_off + 144, primitive_to_bin('float32', obj.current, 4))

    # member: charge, type: float32 (primitive), offset: 148, size: 4
    add_binary(allocator, parent_off + 148, primitive_to_bin('float32', obj.charge, 4))

    # member: capacity, type: float32 (primitive), offset: 152, size: 4
    add_binary(allocator, parent_off + 152, primitive_to_bin('float32', obj.capacity, 4))

    # member: design_capacity, type: float32 (primitive), offset: 156, size: 4
    add_binary(allocator, parent_off + 156, primitive_to_bin('float32', obj.design_capacity, 4))

    # member: percentage, type: float32 (primitive), offset: 160, size: 4
    add_binary(allocator, parent_off + 160, primitive_to_bin('float32', obj.percentage, 4))

    # member: power_supply_status, type: uint8 (primitive), offset: 164, size: 1
    add_binary(allocator, parent_off + 164, primitive_to_bin('uint8', obj.power_supply_status, 1))

    # member: power_supply_health, type: uint8 (primitive), offset: 165, size: 1
    add_binary(allocator, parent_off + 165, primitive_to_bin('uint8', obj.power_supply_health, 1))

    # member: power_supply_technology, type: uint8 (primitive), offset: 166, size: 1
    add_binary(allocator, parent_off + 166, primitive_to_bin('uint8', obj.power_supply_technology, 1))

    # member: present, type: bool (primitive), offset: 168, size: 4
    add_binary(allocator, parent_off + 168, primitive_to_bin('bool', obj.present, 4))

    # member: cell_voltage, type: float32 (primitive), offset: 172, size: 4
    offset_from_heap = heap_data.bytesize
    values = obj.cell_voltage || []
    add_binary(allocator, parent_off + 172, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('float32', values, 4))

    # member: cell_temperature, type: float32 (primitive), offset: 180, size: 4
    offset_from_heap = heap_data.bytesize
    values = obj.cell_temperature || []
    add_binary(allocator, parent_off + 180, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('float32', values, 4))

    # member: location, type: string (primitive), offset: 188, size: 128
    add_binary(allocator, parent_off + 188, primitive_to_bin('string', obj.location, 128))

    # member: serial_number, type: string (primitive), offset: 316, size: 128
    add_binary(allocator, parent_off + 316, primitive_to_bin('string', obj.serial_number, 128))

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
