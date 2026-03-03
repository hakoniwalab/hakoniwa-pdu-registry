#include <fstream>
#include <iostream>

#include "pdu_primitive_ctypes_conv.hpp"

static inline int hako_convert_pdu2cpp_array_string_varray(const Hako_cstring* src, std::vector<std::string>& dst, int len)
{
    return hako_convert_pdu2ros_array_string_varray(src, dst, len);
}

static inline int hako_convert_cpp2pdu_array_string_varray(const std::vector<std::string>& src, Hako_cstring* dst)
{
    return hako_convert_ros2pdu_array_string_varray(src, dst);
}

#include "sensor_msgs/pdu_cpptype_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#include "sensor_msgs/pdu_ctype_JointState.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: joint_state_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_JointState src{};
    src.header.frame_id = "frame";
    src.name = {"a", "b"};
    src.position = {1.0, 2.0};
    src.velocity = {3.0};
    src.effort = {4.0};

    Hako_JointState* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_JointState(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert joint_state to pdu" << std::endl;
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
