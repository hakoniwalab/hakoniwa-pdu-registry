#pragma once

#include "PduRuntime.hpp"

namespace hako::godot_runtime {

enum class PduMetaDataState : int32_t {
    INVALID = 0,
    UNINITIALIZED = 1,
    VALID = 2,
};

inline PduMetaDataState classify_pdu_metadata(const godot::PackedByteArray &binary)
{
    if (binary.size() < PduMetaData::PDU_META_DATA_SIZE) {
        return PduMetaDataState::INVALID;
    }
    bool all_zero = true;
    for (int32_t index = 0; index < PduMetaData::PDU_META_DATA_SIZE; ++index) {
        if (binary[index] != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return PduMetaDataState::UNINITIALIZED;
    }
    return (PduMetaData::read_uint32_le(binary, 0) == PduMetaData::MAGIC_NO &&
            PduMetaData::read_uint32_le(binary, 4) == PduMetaData::VERSION)
        ? PduMetaDataState::VALID
        : PduMetaDataState::INVALID;
}

} // namespace hako::godot_runtime
