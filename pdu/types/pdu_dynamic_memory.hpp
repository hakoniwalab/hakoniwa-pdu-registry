#ifndef _PDU_DYNAMIC_MEMORY_HPP_
#define _PDU_DYNAMIC_MEMORY_HPP_

#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

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
    bool references_overlap(const void* begin, size_t length) const {
        const char* lo = static_cast<const char*>(begin);
        const char* hi = lo + length;
        for (const auto& alloc : allocations) {
            if (alloc.owned || alloc.length == 0) {
                continue;
            }
            const char* a = static_cast<const char*>(alloc.data);
            if (a < hi && lo < a + alloc.length) {
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

#endif /* _PDU_DYNAMIC_MEMORY_HPP_ */
