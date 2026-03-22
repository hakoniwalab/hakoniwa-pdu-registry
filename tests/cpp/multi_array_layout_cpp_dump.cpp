#include <fstream>
#include <iostream>

#include "std_msgs/pdu_cpptype_MultiArrayLayout.hpp"
#include "std_msgs/pdu_cpptype_conv_MultiArrayLayout.hpp"
#include "std_msgs/pdu_ctype_MultiArrayLayout.h"

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
        std::cerr << "usage: multi_array_layout_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_MultiArrayLayout src{};
    src.dim = {
        MakeDim("x", 2, 2),
        MakeDim("y", 3, 6),
    };
    src.data_offset = 9;

    Hako_MultiArrayLayout* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_MultiArrayLayout(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert multi_array_layout to pdu" << std::endl;
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
