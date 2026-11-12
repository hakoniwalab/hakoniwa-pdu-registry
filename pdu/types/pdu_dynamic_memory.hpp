#ifndef _PDU_DYNAMIC_MEMORY_HPP_
#define _PDU_DYNAMIC_MEMORY_HPP_

#include <vector>
#include <cstdlib>
#include <functional>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "pdu_primitive_ctypes.h"

// Class to manage dynamic memory for PDU
class PduDynamicMemory {
public:
    struct Allocation {
        int length;
        int offset;
        void* data;
        bool owned;  // false: data is the caller's (reference()), never freed here

        Allocation(int len, int off, void* ptr, bool own = true)
            : length(len), offset(off), data(ptr), owned(own) {}
    };

    PduDynamicMemory() : current_offset(0) {}
    PduDynamicMemory(const PduDynamicMemory&) = delete;
    PduDynamicMemory& operator=(const PduDynamicMemory&) = delete;

    ~PduDynamicMemory() {
        for (auto& alloc : allocations) {
            if (alloc.owned) {
                free(alloc.data);
            }
        }
    }

    // Allocate memory and store the allocation info.
    //
    // Dynamic PDU length/offset fields are part of the existing binary contract
    // and are represented as int. Compute allocation sizes in size_t, validate
    // that they fit in the 32-bit-compatible PDU offset domain, then convert
    // explicitly so platform compilers cannot silently narrow the value.
    void* allocate(int length, size_t elem_size) {
        const int allocation_size = checked_size(length, elem_size);
        // Zeroed: struct and string slots the converter leaves partly unset
        // (padding, the rest of a fixed string) go into the PDU as zeros.
        void* ptr = calloc(1, allocation_size > 0 ? static_cast<size_t>(allocation_size) : 1);
        if (ptr == nullptr) {
            throw std::runtime_error("Memory allocation failed");
        }
        allocations.emplace_back(allocation_size, current_offset, ptr);
        current_offset += allocation_size;
        return ptr;
    }

    // Place the caller's bytes in the heap without copying them now: they are
    // copied once, by copy_to_pdu(). The data must stay unchanged and alive until
    // then (the converters pass the source message's own arrays). Returns the
    // offset, as get_offset() would for an allocate()d block.
    int reference(const void* data, int length, size_t elem_size) {
        const int allocation_size = checked_size(length, elem_size);
        const int offset = current_offset;
        allocations.emplace_back(allocation_size, offset, const_cast<void*>(data), false);
        current_offset += allocation_size;
        return offset;
    }

private:
    int checked_size(int length, size_t elem_size) const {
        if (length < 0) {
            throw std::invalid_argument("PDU dynamic allocation length must be non-negative");
        }

        const size_t count = static_cast<size_t>(length);
        if (count != 0 && elem_size > std::numeric_limits<size_t>::max() / count) {
            throw std::overflow_error("PDU dynamic allocation size overflow");
        }

        const size_t byte_size = count * elem_size;
        const size_t max_pdu_offset = static_cast<size_t>(std::numeric_limits<int>::max());
        if (byte_size > max_pdu_offset) {
            throw std::overflow_error("PDU dynamic allocation exceeds int-sized length");
        }

        const int allocation_size = static_cast<int>(byte_size);
        if (current_offset > std::numeric_limits<int>::max() - allocation_size) {
            throw std::overflow_error("PDU dynamic allocation exceeds int-sized offset range");
        }
        return allocation_size;
    }

public:

    // Get total size of all allocations
    int get_total_size() const {
        return current_offset;
    }

    // Copy data to a destination buffer and set offsets
    void copy_to_pdu(char* dest) const {
        //std::cout << "dest addr: " << (long long)dest << std::endl;
        for (const auto& alloc : allocations) {
            //std::cout << "dest addr + off: " << (long long)(dest + alloc.offset) << std::endl;
            //std::cout << "length: " << alloc.length << std::endl;
            memcpy(dest + alloc.offset, alloc.data, alloc.length);
        }
    }

    // True when a referenced (caller's) block shares bytes with [begin, begin + length).
    // std::less gives a total order over pointers into different objects, where
    // the built-in < does not.
    bool references_overlap(const void* begin, size_t length) const {
        if (begin == nullptr || length == 0) {
            return false;
        }
        const std::less<const char*> before;
        const char* lo = static_cast<const char*>(begin);
        const char* hi = lo + length;
        for (const auto& alloc : allocations) {
            if (alloc.owned || alloc.length == 0) {
                continue;
            }
            const char* a = static_cast<const char*>(alloc.data);
            const char* a_end = a + alloc.length;
            if (before(a, hi) && before(lo, a_end)) {
                return true;
            }
        }
        return false;
    }

    // Get the offset of a specific allocation
    int get_offset(void* data_ptr) const {
        for (const auto& alloc : allocations) {
            if (alloc.data == data_ptr) {
                return alloc.offset;
            }
        }
        return -1; // Not found
    }

private:
    std::vector<Allocation> allocations;
    int current_offset;
};

// Builds a PDU into buffer, byte for byte as hako_create_empty_pdu() plus the
// base and heap copies lay it out: metadata, the base struct (base_size bytes
// at base), padding, the heap, padding. The buffer needs no alignment and must
// not overlap the heap's referenced blocks. Returns the PDU size, or -1 (with a
// message naming type_name) when it does not fit an int, the buffer is too small
// or null, or overlaps them; nothing is written then.
static inline int hako_pdu_build_into(const char* type_name, const void* base, size_t base_struct_size,
                                      const PduDynamicMemory& heap, char* buffer, int buffer_len)
{
    const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
    const size_t base_size = HAKO_ALIGN_SIZE(base_struct_size, HAKO_ALIGNMENT_SIZE);
    const size_t heap_used = static_cast<size_t>(heap.get_total_size());
    const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
    const size_t pdu_size = meta_size + base_size + heap_size;
    if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "[ConvertorError][" << type_name << "] PDU too large. heap=" << heap_used << std::endl;
        return -1;
    }
    // The whole buffer the caller gave must be clear of the message's arrays.
    if (buffer != nullptr && buffer_len > 0 &&
        heap.references_overlap(buffer, static_cast<size_t>(buffer_len))) {
        std::cerr << "[ConvertorError][" << type_name << "] pdu_buffer overlaps the message's arrays" << std::endl;
        return -1;
    }
    if (buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
        std::cerr << "[ConvertorError][" << type_name << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
        return -1;
    }
    HakoPduMetaDataType meta;
    memset(&meta, 0, sizeof(meta));
    meta.magicno = HAKO_PDU_META_DATA_MAGICNO;
    meta.version = HAKO_PDU_META_DATA_VERSION;
    meta.base_off = static_cast<uint32_t>(meta_size);
    meta.heap_off = static_cast<uint32_t>(meta_size + base_size);
    meta.total_size = static_cast<uint32_t>(pdu_size);
    memset(buffer, 0, meta_size);
    memcpy(buffer, &meta, sizeof(meta));
    char* base_ptr = buffer + meta_size;
    memcpy(base_ptr, base, base_struct_size);
    memset(base_ptr + base_struct_size, 0, base_size - base_struct_size);
    char* heap_ptr = base_ptr + base_size;
    heap.copy_to_pdu(heap_ptr);
    memset(heap_ptr + heap_used, 0, heap_size - heap_used);
    return static_cast<int>(pdu_size);
}

#endif /* _PDU_DYNAMIC_MEMORY_HPP_ */
