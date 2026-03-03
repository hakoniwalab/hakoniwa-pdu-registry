#include <fstream>
#include <iostream>

#include "pdu_primitive_ctypes_conv.hpp"

template<int _src_len, int _dst_len>
static inline int hako_convert_cpu2pdu_array_string(std::array<std::string, _src_len>& src, Hako_cstring dst[])
{
    return hako_convert_ros2pdu_array_string<_src_len, _dst_len>(src, dst);
}

template<int _src_len, int _dst_len>
static inline int hako_convert_pdu2cpp_array_string(Hako_cstring src[], std::array<std::string, _dst_len>& dst)
{
    return hako_convert_pdu2ros_array_string<_src_len, _dst_len>(src, dst);
}

static inline int hako_convert_pdu2cpp_array_string_varray(const Hako_cstring* src, std::vector<std::string>& dst, int len)
{
    return hako_convert_pdu2ros_array_string_varray(src, dst, len);
}

static inline int hako_convert_cpp2pdu_array_string_varray(const std::vector<std::string>& src, Hako_cstring* dst)
{
    return hako_convert_ros2pdu_array_string_varray(src, dst);
}

#include "hako_msgs/pdu_cpptype_SimpleStructVarray.hpp"
#include "hako_msgs/pdu_cpptype_conv_SimpleStructVarray.hpp"
#include "hako_msgs/pdu_ctype_SimpleStructVarray.h"

namespace {

HakoCpp_SimpleVarray MakeSimpleVarray(std::initializer_list<Hako_int8> data, std::initializer_list<Hako_int8> fixed, Hako_int32 p_mem1)
{
    HakoCpp_SimpleVarray value{};
    value.data = std::vector<Hako_int8>(data);
    std::fill(value.fixed_array.begin(), value.fixed_array.end(), 0);
    int index = 0;
    for (auto item : fixed) {
        value.fixed_array[index++] = item;
    }
    value.p_mem1 = p_mem1;
    return value;
}

}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: simple_struct_varray_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_SimpleStructVarray src{};
    src.aaa = 7;
    src.fixed_str = {"alpha", "beta"};
    src.varray_str = {"gamma", "delta"};
    src.fixed_array[0] = MakeSimpleVarray({1, 2}, {3, 4}, 5);
    src.fixed_array[1] = MakeSimpleVarray({6}, {7, 8}, 9);
    src.data = {
        MakeSimpleVarray({10, 11}, {12, 13}, 14),
        MakeSimpleVarray({15}, {16, 17}, 18),
    };

    Hako_SimpleStructVarray* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_SimpleStructVarray(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert simple_struct_varray to pdu" << std::endl;
        return 1;
    }

    auto* top_ptr = static_cast<unsigned char*>(hako_get_top_ptr_pdu(base_ptr));
    if (top_ptr == nullptr) {
        hako_destroy_pdu(base_ptr);
        std::cerr << "failed to get top ptr" << std::endl;
        return 1;
    }

    std::ofstream ofs(argv[1], std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(top_ptr), pdu_size);
    ofs.close();
    hako_destroy_pdu(base_ptr);

    return ofs ? 0 : 1;
}
