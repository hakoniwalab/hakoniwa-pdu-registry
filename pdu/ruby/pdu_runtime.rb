module HakoPdu
  module Runtime
    PDU_META_DATA_SIZE = 24
    PDU_META_DATA_MAGICNO = 0x12345678
    PDU_META_DATA_VERSION = 1

    module PduMetaDataState
      INVALID = 0
      UNINITIALIZED = 1
      VALID = 2
    end

    def self.classify_pdu_metadata(binary_data)
      return PduMetaDataState::INVALID if binary_data.nil?

      bytes = binary_data.b
      return PduMetaDataState::INVALID if bytes.bytesize < PDU_META_DATA_SIZE
      header = bytes.byteslice(0, PDU_META_DATA_SIZE)
      return PduMetaDataState::UNINITIALIZED if header == "\x00".b * PDU_META_DATA_SIZE

      magic, version = header.unpack('V2')
      if magic == PDU_META_DATA_MAGICNO && version == PDU_META_DATA_VERSION
        PduMetaDataState::VALID
      else
        PduMetaDataState::INVALID
      end
    end
  end
end
