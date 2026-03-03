#include <fstream>
#include <iostream>

#include "sensor_msgs/pdu_cpptype_PointCloud2.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"
#include "sensor_msgs/pdu_ctype_PointCloud2.h"

namespace {

HakoCpp_PointField MakePointField(const std::string& name, Hako_uint32 offset, Hako_uint8 datatype, Hako_uint32 count)
{
    HakoCpp_PointField field{};
    field.name = name;
    field.offset = offset;
    field.datatype = datatype;
    field.count = count;
    return field;
}

}  // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: point_cloud2_cpp_dump <output_path>" << std::endl;
        return 1;
    }

    HakoCpp_PointCloud2 src{};
    src.header.stamp.sec = 1;
    src.header.stamp.nanosec = 200;
    src.header.frame_id = "pc";
    src.height = 2;
    src.width = 3;
    src.fields = {
        MakePointField("x", 0, 7, 1),
        MakePointField("intensity", 4, 7, 1),
    };
    src.is_bigendian = false;
    src.point_step = 8;
    src.row_step = 24;
    src.data = {1, 2, 3, 4, 5, 6};
    src.is_dense = true;

    Hako_PointCloud2* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_PointCloud2(src, &base_ptr);
    if (pdu_size <= 0 || base_ptr == nullptr) {
        std::cerr << "failed to convert point_cloud2 to pdu" << std::endl;
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
