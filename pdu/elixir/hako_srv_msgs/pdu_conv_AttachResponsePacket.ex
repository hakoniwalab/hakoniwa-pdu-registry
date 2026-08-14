defmodule HakoPdu.HakoSrvMsgs.AttachResponsePacketConverter do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  def pdu_to_elixir_attach_response_packet(binary_data) when is_binary(binary_data) do
    meta = load_pdu_meta(binary_data)
    obj = HakoPdu.HakoSrvMsgs.AttachResponsePacket.new()
    binary_read_recursive_attach_response_packet(meta, binary_data, obj, meta.base_off)
  end

  def elixir_to_pdu_attach_response_packet(obj) do
    {base_data, heap_data} = binary_write_recursive_attach_response_packet(0, "", "", obj)
    heap_off = @pdu_meta_data_size + byte_size(base_data)
    total_size = heap_off + byte_size(heap_data)
    metadata = <<
      @pdu_meta_data_magicno::little-unsigned-integer-size(32),
      @pdu_meta_data_version::little-unsigned-integer-size(32),
      @pdu_meta_data_size::little-unsigned-integer-size(32),
      heap_off::little-unsigned-integer-size(32),
      total_size::little-unsigned-integer-size(32),
      0::little-unsigned-integer-size(32)
    >>
    metadata <> base_data <> heap_data
  end

  def binary_read_recursive_attach_response_packet(meta, binary_data, obj, base_off) do
    # member: header, type: ServiceResponseHeader (struct), offset: 0, size: 268
    header =
      HakoPdu.HakoSrvMsgs.ServiceResponseHeaderConverter.binary_read_recursive_service_response_header(
        meta,
        binary_data,
        HakoPdu.HakoSrvMsgs.ServiceResponseHeader.new(),
        base_off + 0
      )

    # member: body, type: AttachResponse (struct), offset: 272, size: 40
    body =
      HakoPdu.HakoSrvMsgs.AttachResponseConverter.binary_read_recursive_attach_response(
        meta,
        binary_data,
        HakoPdu.HakoSrvMsgs.AttachResponse.new(),
        base_off + 272
      )

    struct(obj, %{

      header: header,

      body: body

    })
  end

  def binary_write_recursive_attach_response_packet(parent_off, heap_data, allocator, obj) do
    # member: header, type: ServiceResponseHeader (struct), offset: 0, size: 268
    {allocator, heap_data} =
      HakoPdu.HakoSrvMsgs.ServiceResponseHeaderConverter.binary_write_recursive_service_response_header(
        parent_off + 0,
        heap_data,
        allocator,
        obj.header
      )

    # member: body, type: AttachResponse (struct), offset: 272, size: 40
    {allocator, heap_data} =
      HakoPdu.HakoSrvMsgs.AttachResponseConverter.binary_write_recursive_attach_response(
        parent_off + 272,
        heap_data,
        allocator,
        obj.body
      )

    {allocator, heap_data}
  end

  def load_pdu_meta(binary_data) when is_binary(binary_data) do
    if byte_size(binary_data) < @pdu_meta_data_size do
      raise ArgumentError, "PDU is too small for metadata"
    end

    <<
      magic::little-unsigned-integer-size(32),
      version::little-unsigned-integer-size(32),
      base_off::little-unsigned-integer-size(32),
      heap_off::little-unsigned-integer-size(32),
      total_size::little-unsigned-integer-size(32),
      _reserved::little-unsigned-integer-size(32),
      _rest::binary
    >> = binary_data

    if magic != @pdu_meta_data_magicno or version != @pdu_meta_data_version do
      raise ArgumentError, "Invalid PDU metadata"
    end

    %{magic: magic, version: version, base_off: base_off, heap_off: heap_off, total_size: total_size}
  end

  defp add_binary(buffer, offset, data) do
    buffer = if byte_size(buffer) < offset do
      buffer <> :binary.copy(<<0>>, offset - byte_size(buffer))
    else
      buffer
    end

    end_offset = offset + byte_size(data)
    buffer = if byte_size(buffer) < end_offset do
      buffer <> :binary.copy(<<0>>, end_offset - byte_size(buffer))
    else
      buffer
    end

    prefix = binary_part(buffer, 0, offset)
    suffix_offset = offset + byte_size(data)
    suffix_size = byte_size(buffer) - suffix_offset
    suffix = if suffix_size > 0, do: binary_part(buffer, suffix_offset, suffix_size), else: ""
    prefix <> data <> suffix
  end

  defp read_primitive(type, bytes) do
    case type do
      "bool" ->
        <<value::little-unsigned-integer-size(32)>> = bytes
        value != 0
      "byte" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "uint8" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "char" ->
        <<value::unsigned-integer-size(8)>> = bytes
        value
      "int8" ->
        <<value::signed-integer-size(8)>> = bytes
        value
      "int16" ->
        <<value::little-signed-integer-size(16)>> = bytes
        value
      "uint16" ->
        <<value::little-unsigned-integer-size(16)>> = bytes
        value
      "int32" ->
        <<value::little-signed-integer-size(32)>> = bytes
        value
      "uint32" ->
        <<value::little-unsigned-integer-size(32)>> = bytes
        value
      "int64" ->
        <<value::little-signed-integer-size(64)>> = bytes
        value
      "uint64" ->
        <<value::little-unsigned-integer-size(64)>> = bytes
        value
      "float32" ->
        <<value::little-float-size(32)>> = bytes
        value
      "float64" ->
        <<value::little-float-size(64)>> = bytes
        value
      "string" ->
        bytes |> :binary.split(<<0>>) |> List.first()
      _ ->
        raise ArgumentError, "Unsupported primitive type: #{type}"
    end
  end

  defp primitive_to_bin(type, value, size \\ nil) do
    bytes =
      case type do
        "bool" -> <<if(value, do: 1, else: 0)::little-unsigned-integer-size(32)>>
        "byte" -> <<value::unsigned-integer-size(8)>>
        "uint8" -> <<value::unsigned-integer-size(8)>>
        "char" -> <<value::unsigned-integer-size(8)>>
        "int8" -> <<value::signed-integer-size(8)>>
        "int16" -> <<value::little-signed-integer-size(16)>>
        "uint16" -> <<value::little-unsigned-integer-size(16)>>
        "int32" -> <<value::little-signed-integer-size(32)>>
        "uint32" -> <<value::little-unsigned-integer-size(32)>>
        "int64" -> <<value::little-signed-integer-size(64)>>
        "uint64" -> <<value::little-unsigned-integer-size(64)>>
        "float32" -> <<value::little-float-size(32)>>
        "float64" -> <<value::little-float-size(64)>>
        "string" -> to_string(value) <> <<0>>
        _ -> raise ArgumentError, "Unsupported primitive type: #{type}"
      end

    pad_or_trim(bytes, size)
  end

  defp read_primitive_array(_type, _bytes, 0, _element_size), do: []
  defp read_primitive_array(type, bytes, count, element_size) do
    count
    |> range_indices()
    |> Enum.map(fn i ->
      read_primitive(type, binary_part(bytes, i * element_size, element_size))
    end)
  end

  defp primitive_array_to_bin(type, values, element_size \\ nil) do
    (values || [])
    |> Enum.map_join("", &primitive_to_bin(type, &1, element_size))
  end

  defp range_indices(count) when count <= 0, do: []
  defp range_indices(count), do: 0..(count - 1)

  defp pad_or_trim(bytes, nil), do: bytes
  defp pad_or_trim(bytes, size) when byte_size(bytes) > size, do: binary_part(bytes, 0, size)
  defp pad_or_trim(bytes, size), do: bytes <> :binary.copy(<<0>>, size - byte_size(bytes))
end
