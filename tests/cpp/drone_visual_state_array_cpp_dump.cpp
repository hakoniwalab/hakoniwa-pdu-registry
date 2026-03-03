#include <fstream>
#include <iostream>

#include "hako_msgs/pdu_cpptype_DroneVisualState.hpp"
#include "hako_msgs/pdu_cpptype_DroneVisualStateArray.hpp"
#include "hako_msgs/pdu_cpptype_conv_DroneVisualStateArray.hpp"
#include "hako_msgs/pdu_ctype_DroneVisualStateArray.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: drone_visual_state_array_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_DroneVisualStateArray src{};
    src.sequence_id = 42;
    src.chunk_index = 3;
    src.chunk_count = 10;
    src.start_index = 300;
    src.valid_count = 100;
    src.drones.reserve(100);
    for (int i = 0; i < 100; ++i) {
        HakoCpp_DroneVisualState drone{};
        const float base = static_cast<float>(i);
        drone.x = base + 0.1F;
        drone.y = base + 0.2F;
        drone.z = base + 0.3F;
        drone.roll = base + 0.01F;
        drone.pitch = base + 0.02F;
        drone.yaw = base + 0.03F;
        drone.pwm_duty = {
            0.10F + (base * 0.001F),
            0.20F + (base * 0.001F),
            0.30F + (base * 0.001F),
            0.40F + (base * 0.001F),
        };
        src.drones.push_back(drone);
    }

    Hako_DroneVisualStateArray* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_DroneVisualStateArray(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert drone_visual_state_array to pdu" << std::endl;
        return 1;
    }

    auto* top_ptr = static_cast<unsigned char*>(hako_get_top_ptr_pdu(base_ptr));
    if (top_ptr == nullptr) {
        hako_destroy_pdu(base_ptr);
        std::cerr << "failed to get top ptr" << std::endl;
        return 1;
    }
    std::cout << "DroneVisualStateArray total PDU size (100 drones x 4 pwm): " << pdu_size << " bytes" << std::endl;

    std::ofstream ofs(argv[1], std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(top_ptr), pdu_size);
    ofs.close();
    hako_destroy_pdu(base_ptr);

    return ofs ? 0 : 1;
}
