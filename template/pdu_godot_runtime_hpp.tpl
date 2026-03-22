#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/packed_float64_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/variant/packed_int64_array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace hako::godot_runtime {

struct PduMetaData {
    static constexpr int32_t PDU_META_DATA_SIZE = 24;
    static constexpr uint32_t MAGIC_NO = 0x12345678;
    static constexpr uint32_t VERSION = 1;

    uint32_t magic = MAGIC_NO;
    uint32_t version = VERSION;
    int32_t base_off = PDU_META_DATA_SIZE;
    int32_t heap_off = 0;
    int32_t total_size = 0;

    godot::PackedByteArray to_bytes() const
    {
        godot::PackedByteArray bytes;
        bytes.resize(PDU_META_DATA_SIZE);
        write_uint32_le(bytes, 0, magic);
        write_uint32_le(bytes, 4, version);
        write_int32_le(bytes, 8, base_off);
        write_int32_le(bytes, 12, heap_off);
        write_int32_le(bytes, 16, total_size);
        return bytes;
    }

    static bool parse(const godot::PackedByteArray &binary, PduMetaData &out_meta)
    {
        if (binary.size() < PDU_META_DATA_SIZE) {
            return false;
        }
        out_meta.magic = read_uint32_le(binary, 0);
        out_meta.version = read_uint32_le(binary, 4);
        out_meta.base_off = read_int32_le(binary, 8);
        out_meta.heap_off = read_int32_le(binary, 12);
        out_meta.total_size = read_int32_le(binary, 16);
        return (out_meta.magic == MAGIC_NO) && (out_meta.version == VERSION);
    }

    static uint32_t read_uint32_le(const godot::PackedByteArray &binary, int32_t offset)
    {
        return static_cast<uint32_t>(binary[offset]) |
            (static_cast<uint32_t>(binary[offset + 1]) << 8) |
            (static_cast<uint32_t>(binary[offset + 2]) << 16) |
            (static_cast<uint32_t>(binary[offset + 3]) << 24);
    }

    static int32_t read_int32_le(const godot::PackedByteArray &binary, int32_t offset)
    {
        return static_cast<int32_t>(read_uint32_le(binary, offset));
    }

    static void write_uint32_le(godot::PackedByteArray &binary, int32_t offset, uint32_t value)
    {
        binary.set(offset + 0, static_cast<uint8_t>(value & 0xFFu));
        binary.set(offset + 1, static_cast<uint8_t>((value >> 8) & 0xFFu));
        binary.set(offset + 2, static_cast<uint8_t>((value >> 16) & 0xFFu));
        binary.set(offset + 3, static_cast<uint8_t>((value >> 24) & 0xFFu));
    }

    static void write_int32_le(godot::PackedByteArray &binary, int32_t offset, int32_t value)
    {
        write_uint32_le(binary, offset, static_cast<uint32_t>(value));
    }
};

class DynamicAllocator {
public:
    void ensure_size(int32_t size)
    {
        if (_data.size() < size) {
            _data.resize(size);
        }
    }

    int32_t add(const godot::PackedByteArray &bytes, int32_t expected_offset = -1)
    {
        const int32_t offset = (expected_offset >= 0) ? expected_offset : _data.size();
        ensure_size(offset + bytes.size());
        for (int32_t i = 0; i < bytes.size(); ++i) {
            _data.set(offset + i, bytes[i]);
        }
        return offset;
    }

    godot::PackedByteArray to_array() const
    {
        return _data;
    }

    int32_t size() const
    {
        return _data.size();
    }

private:
    godot::PackedByteArray _data;
};

struct BinaryWriterContainer {
    PduMetaData meta;
    DynamicAllocator heap_allocator;
};

inline godot::PackedByteArray read_binary(const godot::PackedByteArray &binary, int32_t offset, int32_t size)
{
    godot::PackedByteArray out;
    out.resize(size);
    for (int32_t i = 0; i < size; ++i) {
        out.set(i, binary[offset + i]);
    }
    return out;
}

inline void write_binary(godot::PackedByteArray &binary, int32_t offset, const godot::PackedByteArray &value)
{
    if (binary.size() < offset + value.size()) {
        binary.resize(offset + value.size());
    }
    for (int32_t i = 0; i < value.size(); ++i) {
        binary.set(offset + i, value[i]);
    }
}

inline godot::PackedByteArray build_pdu(const DynamicAllocator &base_allocator, BinaryWriterContainer &container)
{
    const int32_t total_size = PduMetaData::PDU_META_DATA_SIZE + base_allocator.size() + container.heap_allocator.size();
    container.meta.heap_off = PduMetaData::PDU_META_DATA_SIZE + base_allocator.size();
    container.meta.total_size = total_size;

    godot::PackedByteArray binary;
    binary.resize(total_size);
    write_binary(binary, 0, container.meta.to_bytes());
    write_binary(binary, container.meta.base_off, base_allocator.to_array());
    write_binary(binary, container.meta.heap_off, container.heap_allocator.to_array());
    return binary;
}

inline godot::PackedByteArray zero_bytes(int32_t size)
{
    godot::PackedByteArray bytes;
    bytes.resize(size);
    return bytes;
}

template <typename TInt>
inline godot::PackedByteArray integral_to_bytes(TInt value)
{
    godot::PackedByteArray bytes;
    bytes.resize(sizeof(TInt));
    for (int32_t i = 0; i < static_cast<int32_t>(sizeof(TInt)); ++i) {
        bytes.set(i, static_cast<uint8_t>((static_cast<uint64_t>(value) >> (i * 8)) & 0xFFu));
    }
    return bytes;
}

template <typename TInt>
inline TInt integral_from_bytes(const godot::PackedByteArray &binary, int32_t offset)
{
    uint64_t value = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(sizeof(TInt)); ++i) {
        value |= (static_cast<uint64_t>(binary[offset + i]) << (i * 8));
    }
    return static_cast<TInt>(value);
}

inline bool read_bool(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<int32_t>(binary, offset) != 0; }
inline int8_t read_int8(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<int8_t>(binary, offset); }
inline uint8_t read_uint8(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<uint8_t>(binary, offset); }
inline int16_t read_int16(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<int16_t>(binary, offset); }
inline uint16_t read_uint16(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<uint16_t>(binary, offset); }
inline int32_t read_int32(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<int32_t>(binary, offset); }
inline uint32_t read_uint32(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<uint32_t>(binary, offset); }
inline int64_t read_int64(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<int64_t>(binary, offset); }
inline uint64_t read_uint64(const godot::PackedByteArray &binary, int32_t offset) { return integral_from_bytes<uint64_t>(binary, offset); }

inline float read_float32(const godot::PackedByteArray &binary, int32_t offset)
{
    const uint32_t bits = read_uint32(binary, offset);
    float value = 0.0F;
    std::memcpy(&value, &bits, sizeof(float));
    return value;
}

inline double read_float64(const godot::PackedByteArray &binary, int32_t offset)
{
    const uint64_t bits = read_uint64(binary, offset);
    double value = 0.0;
    std::memcpy(&value, &bits, sizeof(double));
    return value;
}

inline godot::String read_string(const godot::PackedByteArray &binary, int32_t offset, int32_t size)
{
    godot::PackedByteArray raw = read_binary(binary, offset, size);
    int32_t end = 0;
    while ((end < raw.size()) && (raw[end] != 0)) {
        ++end;
    }
    godot::PackedByteArray trimmed;
    trimmed.resize(end);
    for (int32_t i = 0; i < end; ++i) {
        trimmed.set(i, raw[i]);
    }
    return godot::String::utf8(reinterpret_cast<const char *>(trimmed.ptr()), trimmed.size());
}

inline godot::PackedByteArray get_binary_for_bool(bool value) { return integral_to_bytes<int32_t>(value ? 1 : 0); }
inline godot::PackedByteArray get_binary_for_int8(int8_t value) { return integral_to_bytes<int8_t>(value); }
inline godot::PackedByteArray get_binary_for_uint8(uint8_t value) { return integral_to_bytes<uint8_t>(value); }
inline godot::PackedByteArray get_binary_for_int16(int16_t value) { return integral_to_bytes<int16_t>(value); }
inline godot::PackedByteArray get_binary_for_uint16(uint16_t value) { return integral_to_bytes<uint16_t>(value); }
inline godot::PackedByteArray get_binary_for_int32(int32_t value) { return integral_to_bytes<int32_t>(value); }
inline godot::PackedByteArray get_binary_for_uint32(uint32_t value) { return integral_to_bytes<uint32_t>(value); }
inline godot::PackedByteArray get_binary_for_int64(int64_t value) { return integral_to_bytes<int64_t>(value); }
inline godot::PackedByteArray get_binary_for_uint64(uint64_t value) { return integral_to_bytes<uint64_t>(value); }

inline godot::PackedByteArray get_binary_for_float32(float value)
{
    uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(uint32_t));
    return integral_to_bytes<uint32_t>(bits);
}

inline godot::PackedByteArray get_binary_for_float64(double value)
{
    uint64_t bits = 0;
    std::memcpy(&bits, &value, sizeof(uint64_t));
    return integral_to_bytes<uint64_t>(bits);
}

inline godot::PackedByteArray get_binary_for_string(const godot::String &value, int32_t size)
{
    godot::PackedByteArray bytes = value.to_utf8_buffer();
    godot::PackedByteArray out;
    out.resize(size);
    const int32_t copy_len = (size > 0) ? std::min<int32_t>(bytes.size(), size - 1) : 0;
    for (int32_t i = 0; i < copy_len; ++i) {
        out.set(i, bytes[i]);
    }
    if (size > 0) {
        out.set(copy_len, 0);
    }
    return out;
}

inline bool variant_to_bool(const godot::Variant &value) { return static_cast<bool>(value); }
inline int8_t variant_to_int8(const godot::Variant &value) { return static_cast<int8_t>(static_cast<int64_t>(value)); }
inline uint8_t variant_to_uint8(const godot::Variant &value) { return static_cast<uint8_t>(static_cast<int64_t>(value)); }
inline int16_t variant_to_int16(const godot::Variant &value) { return static_cast<int16_t>(static_cast<int64_t>(value)); }
inline uint16_t variant_to_uint16(const godot::Variant &value) { return static_cast<uint16_t>(static_cast<int64_t>(value)); }
inline int32_t variant_to_int32(const godot::Variant &value) { return static_cast<int32_t>(static_cast<int64_t>(value)); }
inline uint32_t variant_to_uint32(const godot::Variant &value) { return static_cast<uint32_t>(static_cast<int64_t>(value)); }
inline int64_t variant_to_int64(const godot::Variant &value) { return static_cast<int64_t>(value); }
inline uint64_t variant_to_uint64(const godot::Variant &value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }
inline float variant_to_float32(const godot::Variant &value) { return static_cast<double>(value); }
inline double variant_to_float64(const godot::Variant &value) { return static_cast<double>(value); }
inline godot::String variant_to_string(const godot::Variant &value) { return static_cast<godot::String>(value); }
inline godot::Array variant_to_array(const godot::Variant &value) { return static_cast<godot::Array>(value); }
inline godot::Dictionary variant_to_dictionary(const godot::Variant &value) { return static_cast<godot::Dictionary>(value); }
inline godot::PackedByteArray variant_to_packed_byte_array(const godot::Variant &value) { return static_cast<godot::PackedByteArray>(value); }
inline godot::PackedInt32Array variant_to_packed_int32_array(const godot::Variant &value) { return static_cast<godot::PackedInt32Array>(value); }
inline godot::PackedInt64Array variant_to_packed_int64_array(const godot::Variant &value) { return static_cast<godot::PackedInt64Array>(value); }
inline godot::PackedFloat32Array variant_to_packed_float32_array(const godot::Variant &value) { return static_cast<godot::PackedFloat32Array>(value); }
inline godot::PackedFloat64Array variant_to_packed_float64_array(const godot::Variant &value) { return static_cast<godot::PackedFloat64Array>(value); }

} // namespace hako::godot_runtime
