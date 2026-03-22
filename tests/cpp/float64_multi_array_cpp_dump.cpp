#include <fstream>
#include <iostream>

#include "std_msgs/pdu_cpptype_Float64MultiArray.hpp"
#include "std_msgs/pdu_cpptype_conv_Float64MultiArray.hpp"
#include "std_msgs/pdu_ctype_Float64MultiArray.h"

namespace {

HakoCpp_MultiArrayDimension MakeDim(const std::string& label, Hako_uint32 size, Hako_uint32 stride)
{
    HakoCpp_MultiArrayDimension dim{};
    dim.label = label;
    dim.size = size;
    dim.stride = stride;
    return dim;
}

}  // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: float64_multi_array_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_Float64MultiArray src{};
    src.layout.dim = {
        MakeDim("x", 2, 2),
        MakeDim("y", 3, 6),
    };
    src.layout.data_offset = 9;
    src.data = {1.5, 2.5};

    Hako_Float64MultiArray* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_Float64MultiArray(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert float64_multi_array to pdu" << std::endl;
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
