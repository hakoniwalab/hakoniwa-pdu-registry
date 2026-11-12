#ifndef _PDU_PRIMITIVE_CTYPES_CONV_HPP_
#define _PDU_PRIMITIVE_CTYPES_CONV_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cstring>

// A string into a fixed char array of dst_size bytes: at most dst_size - 1
// characters, the terminating '\0' always inside the array (a longer string is
// cut). The rest of the array is left as it is.
static inline void hako_convert_string_to_pdu(const std::string &src, char *dst, size_t dst_size)
{
    if (dst_size == 0) {
        return;
    }
    const size_t len = std::min(src.length(), dst_size - 1);
    memcpy(dst, src.data(), len);
    dst[len] = '\0';
}
// A fixed char array of src_size bytes as a string: up to its first '\0', or
// all of it when it has none (another writer may fill it to the end).
static inline std::string hako_convert_string_from_pdu(const char *src, size_t src_size)
{
    return std::string(src, strnlen(src, src_size));
}

#define M_SIZE(type, mem)   sizeof(((type *)0)->mem)
#define M_ARRAY_SIZE(type, mem_type, mem)       (M_SIZE(type, mem) / sizeof(mem_type))

template <class PduPrimitiveType, class RosPrimitiveType> 
void hako_convert_pdu2ros(PduPrimitiveType &src, RosPrimitiveType &dst)
{
    dst = src;
    return;
}
template <class PduPrimitiveType, class RosPrimitiveType> 
int hako_convert_pdu2ros_array(PduPrimitiveType src[], int src_len, RosPrimitiveType &dst, int dst_len)
{
    int ret = 0;
    int len = dst_len;
    if (src_len < dst_len) {
        len = src_len;
        ret = -1;
    }
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    return ret;
}

template <class PduPrimitiveType, class RosPrimitiveType> 
int hako_convert_pdu2ros_array(PduPrimitiveType src[], int src_len, std::vector<RosPrimitiveType> &dst, int dst_len)
{
    if (dst_len < src_len) {
        dst.resize(src_len);
    }
    for (int i = 0; i < src_len; i++) {
        dst[i] = src[i];
    }
    return 0;
}

template <class RosPrimitiveType, class PduPrimitiveType> 
void hako_convert_ros2pdu(RosPrimitiveType &src, PduPrimitiveType &dst)
{
    dst = src;
    return;
}
template <class RosPrimitiveType, class PduPrimitiveType> 
int hako_convert_ros2pdu_array(RosPrimitiveType &src, int src_len, PduPrimitiveType &dst, int dst_len)
{
    int ret = 0;
    int len = dst_len;
    if (src_len < dst_len) {
        len = src_len;
        ret = -1;
    }
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    return ret;
}

template<int _src_len, int _dst_len>
int hako_convert_pdu2ros_array_string(Hako_cstring src[], std::array<std::string, _dst_len> &dst)
{
    int ret = 0;
    int len = _dst_len;
    if (_dst_len > _src_len) {
        len = _src_len;
        ret = -1;
    }
    for (int i = 0; i < len; i++) {
        dst[i] = hako_convert_string_from_pdu(src[i].data, sizeof(src[i].data));
    }
    return ret;
}
template<int _src_len, int _dst_len>
int hako_convert_pdu2ros_array_string(Hako_cstring src[], std::vector<std::string> &dst)
{
    int ret = 0;
    int len = _dst_len;
    if (_dst_len > _src_len) {
        len = _src_len;
        ret = -1;
    }
    dst.resize(len);
    for (int i = 0; i < len; i++) {
        dst[i] = hako_convert_string_from_pdu(src[i].data, sizeof(src[i].data));
    }
    return ret;
}
static inline int hako_convert_pdu2ros_array_string_varray(const Hako_cstring* src, std::vector<std::string> &dst, int len)
{
    int ret = 0;
    dst.resize(len);
    for (int i = 0; i < len; i++) {
        dst[i] = hako_convert_string_from_pdu(src[i].data, sizeof(src[i].data));
    }
    return ret;
}

template<int _src_len, int _dst_len>
int hako_convert_ros2pdu_array_string(std::array<std::string, _src_len> &src, Hako_cstring dst[])
{
    int ret = 0;
    int len = _dst_len;
    if (_dst_len > _src_len) {
        len = _src_len;
        ret = -1;
    }
    for (int i = 0; i < len; i++) {
        int cplen = src[i].length();
        if (cplen >= (HAKO_STRING_SIZE - 1)) {
            cplen = HAKO_STRING_SIZE - 2;
        }
        else {
            cplen = src[i].length();
        }
        for (int j = 0; j < cplen; j++) {
            dst[i].data[j] = src[i][j];
        }
        dst[i].data[cplen] = '\0';
    }
    return ret;
}

static inline int hako_convert_ros2pdu_array_string_varray(const std::vector<std::string> &src, Hako_cstring *dst)
{
    int ret = 0;
    int len = src.size();
    for (int i = 0; i < len; i++) {
        int cplen = src[i].length();
        if (cplen >= (HAKO_STRING_SIZE - 1)) {
            cplen = HAKO_STRING_SIZE - 2;
        }
        else {
            cplen = src[i].length();
        }
        for (int j = 0; j < cplen; j++) {
            dst[i].data[j] = src[i][j];
        }
        dst[i].data[cplen] = '\0';
    }
    return ret;
}

// The generated C++ converters (template/pdu_cpptypes_conv_cpp.tpl) call the string-array helpers
// by their *_cpp_* names. They are the same conversions as the *_ros_* helpers above.
// Users that already map these names with #define keep working: the functions are skipped then.
#ifndef hako_convert_pdu2cpp_array_string_varray
static inline int hako_convert_pdu2cpp_array_string_varray(const Hako_cstring* src, std::vector<std::string> &dst, int len)
{
    return hako_convert_pdu2ros_array_string_varray(src, dst, len);
}
#endif
#ifndef hako_convert_cpp2pdu_array_string_varray
static inline int hako_convert_cpp2pdu_array_string_varray(const std::vector<std::string> &src, Hako_cstring *dst)
{
    return hako_convert_ros2pdu_array_string_varray(src, dst);
}
#endif

template<int _src_len, int _dst_len>
int hako_convert_ros2pdu_array_string(std::vector<std::string> &src, Hako_cstring dst[])
{
    int ret = 0;
    int len = _dst_len;
    if (_dst_len > _src_len) {
        len = _src_len;
        ret = -1;
    }
    if (static_cast<int>(src.size()) < len) {  // never read past the vector
        len = static_cast<int>(src.size());
        ret = -1;
    }
    for (int i = 0; i < len; i++) {
        int cplen = src[i].length();
        if (cplen >= (HAKO_STRING_SIZE - 1)) {
            cplen = HAKO_STRING_SIZE - 2;
        }
        else {
            cplen = src[i].length();
        }
        for (int j = 0; j < cplen; j++) {
            dst[i].data[j] = src[i][j];
        }
        dst[i].data[cplen] = '\0';
    }
    return ret;
}

#define hako_convert_pdu2cpp hako_convert_pdu2ros
#define hako_convert_cpp2pdu hako_convert_ros2pdu
#define hako_convert_cpp2pdu_array hako_convert_ros2pdu_array

#endif /* _PDU_PRIMITIVE_CTYPES_CONV_HPP_ */