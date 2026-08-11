defmodule HakoPdu.Runtime do
  @pdu_meta_data_size 24
  @pdu_meta_data_magicno 0x12345678
  @pdu_meta_data_version 1

  defmodule PduMetaDataState do
    def invalid, do: 0
    def uninitialized, do: 1
    def valid, do: 2
  end

  def classify_pdu_metadata(nil), do: PduMetaDataState.invalid()

  def classify_pdu_metadata(binary_data) when is_binary(binary_data) do
    cond do
      byte_size(binary_data) < @pdu_meta_data_size ->
        PduMetaDataState.invalid()

      binary_part(binary_data, 0, @pdu_meta_data_size) == :binary.copy(<<0>>, @pdu_meta_data_size) ->
        PduMetaDataState.uninitialized()

      true ->
        <<magic::little-unsigned-integer-size(32),
          version::little-unsigned-integer-size(32), _rest::binary>> = binary_data

        if magic == @pdu_meta_data_magicno && version == @pdu_meta_data_version do
          PduMetaDataState.valid()
        else
          PduMetaDataState.invalid()
        end
    end
  end

  def classify_pdu_metadata(_), do: PduMetaDataState.invalid()
end
