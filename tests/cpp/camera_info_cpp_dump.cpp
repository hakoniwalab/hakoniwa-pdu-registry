#include <fstream>
#include <iostream>

#include "sensor_msgs/pdu_cpptype_CameraInfo.hpp"
#include "sensor_msgs/pdu_cpptype_conv_CameraInfo.hpp"
#include "sensor_msgs/pdu_ctype_CameraInfo.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: camera_info_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_CameraInfo src{};
    src.header.stamp.sec = 1;
    src.header.stamp.nanosec = 200;
    src.header.frame_id = "cam";
    src.height = 480;
    src.width = 640;
    src.distortion_model = "plumb_bob";
    src.d = {0.1, 0.2};
    src.k.fill(1.0);
    src.r.fill(2.0);
    src.p.fill(3.0);
    src.binning_x = 1;
    src.binning_y = 2;
    src.roi.x_offset = 3;
    src.roi.y_offset = 4;
    src.roi.height = 5;
    src.roi.width = 6;
    src.roi.do_rectify = true;

    Hako_CameraInfo* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_CameraInfo(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert camera_info to pdu" << std::endl;
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
