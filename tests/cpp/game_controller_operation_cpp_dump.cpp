#include <fstream>
#include <iostream>

#include "hako_msgs/pdu_cpptype_GameControllerOperation.hpp"
#include "hako_msgs/pdu_cpptype_conv_GameControllerOperation.hpp"
#include "hako_msgs/pdu_ctype_GameControllerOperation.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: game_controller_operation_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_GameControllerOperation src{};
    src.axis = {0.5, -1.0, 2.0, -3.0, 4.0, -5.0};
    src.button = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

    Hako_GameControllerOperation* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_GameControllerOperation(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert game_controller_operation to pdu" << std::endl;
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
