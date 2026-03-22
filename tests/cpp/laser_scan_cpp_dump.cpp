#include <fstream>
#include <iostream>

#include "sensor_msgs/pdu_cpptype_LaserScan.hpp"
#include "sensor_msgs/pdu_cpptype_conv_LaserScan.hpp"
#include "sensor_msgs/pdu_ctype_LaserScan.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: laser_scan_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_LaserScan src{};
    src.header.stamp.sec = 1;
    src.header.stamp.nanosec = 200;
    src.header.frame_id = "laser";
    src.angle_min = -1.0f;
    src.angle_max = 1.0f;
    src.angle_increment = 0.5f;
    src.time_increment = 0.1f;
    src.scan_time = 0.2f;
    src.range_min = 0.3f;
    src.range_max = 30.0f;
    src.ranges = {1.5f, 2.5f};
    src.intensities = {10.0f, 20.0f};

    Hako_LaserScan* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_LaserScan(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert laser_scan to pdu" << std::endl;
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
