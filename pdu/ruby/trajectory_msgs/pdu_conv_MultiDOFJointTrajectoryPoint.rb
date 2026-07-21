require_relative 'pdu_type_MultiDOFJointTrajectoryPoint'
require_relative '../geometry_msgs/pdu_type_Transform'
require_relative '../geometry_msgs/pdu_conv_Transform'
require_relative '../geometry_msgs/pdu_type_Twist'
require_relative '../geometry_msgs/pdu_conv_Twist'
require_relative '../builtin_interfaces/pdu_type_Duration'
require_relative '../builtin_interfaces/pdu_conv_Duration'


module HakoPdu::TrajectoryMsgs::MultiDOFJointTrajectoryPointConverter
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_multi_d_o_f_joint_trajectory_point(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu::TrajectoryMsgs::MultiDOFJointTrajectoryPoint.new
    binary_read_recursive_multi_d_o_f_joint_trajectory_point(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_multi_d_o_f_joint_trajectory_point(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_multi_d_o_f_joint_trajectory_point(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_multi_d_o_f_joint_trajectory_point(meta, binary_data, obj, base_off)
    # member: transforms, type: geometry_msgs/Transform (struct), offset: 0, size: 56
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 0, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 0 + 4, 4))
    obj.transforms = []
    array_size.times do |i|
      child = HakoPdu::GeometryMsgs::Transform.new
      HakoPdu::GeometryMsgs::TransformConverter.binary_read_recursive_transform(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 56)
      obj.transforms << child
    end

    # member: velocities, type: geometry_msgs/Twist (struct), offset: 8, size: 48
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 8, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 8 + 4, 4))
    obj.velocities = []
    array_size.times do |i|
      child = HakoPdu::GeometryMsgs::Twist.new
      HakoPdu::GeometryMsgs::TwistConverter.binary_read_recursive_twist(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 48)
      obj.velocities << child
    end

    # member: accelerations, type: geometry_msgs/Twist (struct), offset: 16, size: 48
    array_size = read_primitive('int32', binary_data.byteslice(base_off + 16, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + 16 + 4, 4))
    obj.accelerations = []
    array_size.times do |i|
      child = HakoPdu::GeometryMsgs::Twist.new
      HakoPdu::GeometryMsgs::TwistConverter.binary_read_recursive_twist(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * 48)
      obj.accelerations << child
    end

    # member: time_from_start, type: builtin_interfaces/Duration (struct), offset: 24, size: 8
    obj.time_from_start = HakoPdu::BuiltinInterfaces::Duration.new
    HakoPdu::BuiltinInterfaces::DurationConverter.binary_read_recursive_duration(meta, binary_data, obj.time_from_start, base_off + 24)

    obj
  end

  def self.binary_write_recursive_multi_d_o_f_joint_trajectory_point(parent_off, heap_data, allocator, obj)
    # member: transforms, type: geometry_msgs/Transform (struct), offset: 0, size: 56
    offset_from_heap = heap_data.bytesize
    values = obj.transforms || []
    add_binary(allocator, parent_off + 0, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 56))
    values.each_with_index do |child, i|
      HakoPdu::GeometryMsgs::TransformConverter.binary_write_recursive_transform(offset_from_heap + i * 56, heap_data, heap_data, child)
    end

    # member: velocities, type: geometry_msgs/Twist (struct), offset: 8, size: 48
    offset_from_heap = heap_data.bytesize
    values = obj.velocities || []
    add_binary(allocator, parent_off + 8, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 48))
    values.each_with_index do |child, i|
      HakoPdu::GeometryMsgs::TwistConverter.binary_write_recursive_twist(offset_from_heap + i * 48, heap_data, heap_data, child)
    end

    # member: accelerations, type: geometry_msgs/Twist (struct), offset: 16, size: 48
    offset_from_heap = heap_data.bytesize
    values = obj.accelerations || []
    add_binary(allocator, parent_off + 16, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * 48))
    values.each_with_index do |child, i|
      HakoPdu::GeometryMsgs::TwistConverter.binary_write_recursive_twist(offset_from_heap + i * 48, heap_data, heap_data, child)
    end

    # member: time_from_start, type: builtin_interfaces/Duration (struct), offset: 24, size: 8
    HakoPdu::BuiltinInterfaces::DurationConverter.binary_write_recursive_duration(parent_off + 24, heap_data, allocator, obj.time_from_start)

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
