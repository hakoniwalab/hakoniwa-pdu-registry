require_relative 'pdu_type_{{ container.msg_type_name }}'
{% for imp in container.ruby_conv_imports -%}
{%- if imp.dep_pkg == container.pkg_name -%}
require_relative '{{ imp.type_file }}'
require_relative '{{ imp.conv_file }}'
{%- else -%}
require_relative '../{{ imp.dep_pkg }}/{{ imp.type_file }}'
require_relative '../{{ imp.dep_pkg }}/{{ imp.conv_file }}'
{%- endif %}
{% endfor %}

module {{ container.converter_module_name }}
  PDU_META_DATA_SIZE = 24
  PDU_META_DATA_MAGICNO = 0x12345678
  PDU_META_DATA_VERSION = 1

  def self.pdu_to_ruby_{{ container.func_name }}(binary_data)
    meta = load_pdu_meta(binary_data)
    obj = {{ container.module_name }}.new
    binary_read_recursive_{{ container.func_name }}(meta, binary_data.b, obj, meta[:base_off])
    obj
  end

  def self.ruby_to_pdu_{{ container.func_name }}(obj)
    base_data = ''.b
    heap_data = ''.b
    binary_write_recursive_{{ container.func_name }}(0, heap_data, base_data, obj)
    heap_off = PDU_META_DATA_SIZE + base_data.bytesize
    total_size = heap_off + heap_data.bytesize
    metadata = [PDU_META_DATA_MAGICNO, PDU_META_DATA_VERSION, PDU_META_DATA_SIZE, heap_off, total_size, 0].pack('V6')
    metadata + base_data + heap_data
  end

  def self.binary_read_recursive_{{ container.func_name }}(meta, binary_data, obj, base_off)
{%- for item in container.offset_data %}
{%- set field_func = container.convert_snake(item.member_name) if container.convert_snake is defined else item.member_name %}
    # member: {{ item.member_name }}, type: {{ item.type_name }} ({{ item.data_type }}), offset: {{ item.offset }}, size: {{ item.size }}
{%- if item.data_type == 'primitive' or item.data_type == 'string' %}
{%- if item.array_type == 'single' %}
    obj.{{ item.member_name }} = read_primitive('{{ item.type_name }}', binary_data.byteslice(base_off + {{ item.offset }}, {{ item.size }}))
{%- elif item.array_type == 'array' %}
    obj.{{ item.member_name }} = read_primitive_array('{{ container.get_array_type(item.type_name) }}', binary_data.byteslice(base_off + {{ item.offset }}, {{ item.size }}), {{ item.array_len }}, {{ item.size }} / {{ item.array_len }})
{%- else %}
    array_size = read_primitive('int32', binary_data.byteslice(base_off + {{ item.offset }}, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + {{ item.offset }} + 4, 4))
    obj.{{ item.member_name }} = read_primitive_array('{{ item.type_name }}', binary_data.byteslice(meta[:heap_off] + offset_from_heap, {{ item.size }} * array_size), array_size, {{ item.size }})
{%- endif %}
{%- else %}
{%- if item.array_type == 'single' %}
    obj.{{ item.member_name }} = {{ container.get_ruby_type_ref(item.type_name) }}.new
    {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(meta, binary_data, obj.{{ item.member_name }}, base_off + {{ item.offset }})
{%- elif item.array_type == 'array' %}
    obj.{{ item.member_name }} = []
    {{ item.array_len }}.times do |i|
      child = {{ container.get_ruby_type_ref(item.type_name) }}.new
      {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(meta, binary_data, child, base_off + {{ item.offset }} + i * ({{ item.size }} / {{ item.array_len }}))
      obj.{{ item.member_name }} << child
    end
{%- else %}
    array_size = read_primitive('int32', binary_data.byteslice(base_off + {{ item.offset }}, 4))
    offset_from_heap = read_primitive('int32', binary_data.byteslice(base_off + {{ item.offset }} + 4, 4))
    obj.{{ item.member_name }} = []
    array_size.times do |i|
      child = {{ container.get_ruby_type_ref(item.type_name) }}.new
      {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_read_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(meta, binary_data, child, meta[:heap_off] + offset_from_heap + i * {{ item.size }})
      obj.{{ item.member_name }} << child
    end
{%- endif %}
{%- endif %}
{% endfor %}
    obj
  end

  def self.binary_write_recursive_{{ container.func_name }}(parent_off, heap_data, allocator, obj)
{%- for item in container.offset_data %}
    # member: {{ item.member_name }}, type: {{ item.type_name }} ({{ item.data_type }}), offset: {{ item.offset }}, size: {{ item.size }}
{%- if item.data_type == 'primitive' or item.data_type == 'string' %}
{%- if item.array_type == 'single' %}
    add_binary(allocator, parent_off + {{ item.offset }}, primitive_to_bin('{{ item.type_name }}', obj.{{ item.member_name }}, {{ item.size }}))
{%- elif item.array_type == 'array' %}
    add_binary(allocator, parent_off + {{ item.offset }}, primitive_array_to_bin('{{ container.get_array_type(item.type_name) }}', obj.{{ item.member_name }}, {{ item.size }} / {{ item.array_len }}))
{%- else %}
    offset_from_heap = heap_data.bytesize
    values = obj.{{ item.member_name }} || []
    add_binary(allocator, parent_off + {{ item.offset }}, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, primitive_array_to_bin('{{ item.type_name }}', values, {{ item.size }}))
{%- endif %}
{%- else %}
{%- if item.array_type == 'single' %}
    {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(parent_off + {{ item.offset }}, heap_data, allocator, obj.{{ item.member_name }})
{%- elif item.array_type == 'array' %}
    (obj.{{ item.member_name }} || []).each_with_index do |child, i|
      {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(parent_off + {{ item.offset }} + i * ({{ item.size }} / {{ item.array_len }}), heap_data, allocator, child)
    end
{%- else %}
    offset_from_heap = heap_data.bytesize
    values = obj.{{ item.member_name }} || []
    add_binary(allocator, parent_off + {{ item.offset }}, [values.length, offset_from_heap].pack('l<l<'))
    add_binary(heap_data, offset_from_heap, "\x00".b * (values.length * {{ item.size }}))
    values.each_with_index do |child, i|
      {{ container.get_ruby_type_ref(item.type_name) }}Converter.binary_write_recursive_{{ container.convert_snake(container.get_msg_type(item.type_name)) }}(offset_from_heap + i * {{ item.size }}, heap_data, heap_data, child)
    end
{%- endif %}
{%- endif %}
{% endfor %}
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
