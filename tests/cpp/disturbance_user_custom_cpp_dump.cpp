#include <fstream>
#include <iostream>

#include "hako_msgs/pdu_cpptype_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_ctype_DisturbanceUserCustom.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: disturbance_user_custom_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_DisturbanceUserCustom src{};
    src.data = {1.25, 2.5};

    Hako_DisturbanceUserCustom* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_DisturbanceUserCustom(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert disturbance_user_custom to pdu" << std::endl;
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
