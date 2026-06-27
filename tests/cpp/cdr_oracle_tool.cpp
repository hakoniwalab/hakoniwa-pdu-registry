#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "hako_msgs/pdu_cpptype_cdr_conv_GameControllerOperation.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_SimpleStructVarray.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_PointCloud2.hpp"

namespace {

template <typename T>
std::string NumberArrayJson(const T& values)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << +values[i];
    }
    oss << "]";
    return oss.str();
}

template <typename T>
std::string BoolArrayJson(const T& values)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << (values[i] ? "true" : "false");
    }
    oss << "]";
    return oss.str();
}

std::string StringJson(const std::string& value)
{
    std::ostringstream oss;
    oss << "\"";
    for (char ch : value) {
        switch (ch) {
        case '\\':
            oss << "\\\\";
            break;
        case '"':
            oss << "\\\"";
            break;
        case '\n':
            oss << "\\n";
            break;
        case '\r':
            oss << "\\r";
            break;
        case '\t':
            oss << "\\t";
            break;
        default:
            oss << ch;
            break;
        }
    }
    oss << "\"";
    return oss.str();
}

std::string StringArrayJson(const std::vector<std::string>& values)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << StringJson(values[i]);
    }
    oss << "]";
    return oss.str();
}

HakoCpp_SimpleVarray MakeSimpleVarray(
    std::initializer_list<Hako_int8> data,
    std::initializer_list<Hako_int8> fixed,
    Hako_int32 p_mem1)
{
    HakoCpp_SimpleVarray value{};
    value.data = std::vector<Hako_int8>(data);
    std::fill(value.fixed_array.begin(), value.fixed_array.end(), 0);
    size_t index = 0;
    for (auto item : fixed) {
        value.fixed_array[index++] = item;
    }
    value.p_mem1 = p_mem1;
    return value;
}

HakoCpp_PointField MakePointField(
    const std::string& name,
    Hako_uint32 offset,
    Hako_uint8 datatype,
    Hako_uint32 count)
{
    HakoCpp_PointField field{};
    field.name = name;
    field.offset = offset;
    field.datatype = datatype;
    field.count = count;
    return field;
}

HakoCpp_GameControllerOperation MakeGameControllerOperation()
{
    HakoCpp_GameControllerOperation src{};
    src.axis = {0.5, -1.0, 2.0, -3.0, 4.0, -5.0};
    src.button = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
    return src;
}

HakoCpp_JointState MakeJointState()
{
    HakoCpp_JointState src{};
    src.header.stamp.sec = 12;
    src.header.stamp.nanosec = 345;
    src.header.frame_id = "joint_frame";
    src.name = {"joint_a", "joint_b"};
    src.position = {1.0, 2.0};
    src.velocity = {3.0};
    src.effort = {4.0, 5.0, 6.0};
    return src;
}

HakoCpp_PointCloud2 MakePointCloud2()
{
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
    src.is_bigendian = 0;
    src.point_step = 8;
    src.row_step = 24;
    src.data = {1, 2, 3, 4, 5, 6};
    src.is_dense = 1;
    return src;
}

HakoCpp_SimpleStructVarray MakeSimpleStructVarray()
{
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
    return src;
}

std::string ToJson(const HakoCpp_GameControllerOperation& value)
{
    std::ostringstream oss;
    oss << "{\"axis\":" << NumberArrayJson(value.axis)
        << ",\"button\":" << BoolArrayJson(value.button)
        << "}";
    return oss.str();
}

std::string ToJson(const HakoCpp_JointState& value)
{
    std::ostringstream oss;
    oss << "{\"header\":{\"stamp\":{\"sec\":" << value.header.stamp.sec
        << ",\"nanosec\":" << value.header.stamp.nanosec
        << "},\"frame_id\":" << StringJson(value.header.frame_id)
        << "},\"name\":" << StringArrayJson(value.name)
        << ",\"position\":" << NumberArrayJson(value.position)
        << ",\"velocity\":" << NumberArrayJson(value.velocity)
        << ",\"effort\":" << NumberArrayJson(value.effort)
        << "}";
    return oss.str();
}

std::string ToJson(const HakoCpp_PointField& value)
{
    std::ostringstream oss;
    oss << "{\"name\":" << StringJson(value.name)
        << ",\"offset\":" << value.offset
        << ",\"datatype\":" << +value.datatype
        << ",\"count\":" << value.count
        << "}";
    return oss.str();
}

std::string ToJson(const HakoCpp_PointCloud2& value)
{
    std::ostringstream oss;
    oss << "{\"header\":{\"stamp\":{\"sec\":" << value.header.stamp.sec
        << ",\"nanosec\":" << value.header.stamp.nanosec
        << "},\"frame_id\":" << StringJson(value.header.frame_id)
        << "},\"height\":" << value.height
        << ",\"width\":" << value.width
        << ",\"fields\":[";
    for (size_t i = 0; i < value.fields.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << ToJson(value.fields[i]);
    }
    oss << "],\"is_bigendian\":" << (value.is_bigendian ? "true" : "false")
        << ",\"point_step\":" << value.point_step
        << ",\"row_step\":" << value.row_step
        << ",\"data\":" << NumberArrayJson(value.data)
        << ",\"is_dense\":" << (value.is_dense ? "true" : "false")
        << "}";
    return oss.str();
}

std::string ToJson(const HakoCpp_SimpleVarray& value)
{
    std::ostringstream oss;
    oss << "{\"data\":" << NumberArrayJson(value.data)
        << ",\"fixed_array\":" << NumberArrayJson(value.fixed_array)
        << ",\"p_mem1\":" << value.p_mem1
        << "}";
    return oss.str();
}

std::string ToJson(const HakoCpp_SimpleStructVarray& value)
{
    std::vector<std::string> fixed_str(value.fixed_str.begin(), value.fixed_str.end());
    std::ostringstream oss;
    oss << "{\"aaa\":" << value.aaa
        << ",\"fixed_str\":" << StringArrayJson(fixed_str)
        << ",\"varray_str\":" << StringArrayJson(value.varray_str)
        << ",\"fixed_array\":[";
    for (size_t i = 0; i < value.fixed_array.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << ToJson(value.fixed_array[i]);
    }
    oss << "],\"data\":[";
    for (size_t i = 0; i < value.data.size(); ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << ToJson(value.data[i]);
    }
    oss << "]}";
    return oss.str();
}

bool WritePayload(const std::string& path, const std::vector<uint8_t>& payload)
{
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(payload.data()), static_cast<std::streamsize>(payload.size()));
    return static_cast<bool>(ofs);
}

std::vector<uint8_t> ReadPayload(const std::string& path)
{
    std::ifstream ifs(path, std::ios::binary);
    return std::vector<uint8_t>(
        std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>());
}

template <typename T, typename EncodeFn>
int EncodeCase(const std::string& path, const T& value, EncodeFn encode)
{
    std::vector<uint8_t> payload;
    if (encode(value, payload) <= 0) {
        std::cerr << "failed to encode CDR payload" << std::endl;
        return 1;
    }
    if (!WritePayload(path, payload)) {
        std::cerr << "failed to write CDR payload: " << path << std::endl;
        return 1;
    }
    return 0;
}

template <typename T, typename DecodeFn>
int DecodeCase(const std::string& path, DecodeFn decode)
{
    const auto payload = ReadPayload(path);
    T restored{};
    if (!decode(payload, restored)) {
        std::cerr << "failed to decode CDR payload: " << path << std::endl;
        return 1;
    }
    std::cout << ToJson(restored) << std::endl;
    return 0;
}

int Encode(const std::string& case_name, const std::string& path)
{
    if (case_name == "game_controller_operation") {
        return EncodeCase(path, MakeGameControllerOperation(), [](const auto& value, auto& payload) {
            return hako_convert_cpp2cdr_GameControllerOperation(value, payload);
        });
    }
    if (case_name == "joint_state") {
        return EncodeCase(path, MakeJointState(), [](const auto& value, auto& payload) {
            return hako_convert_cpp2cdr_JointState(value, payload);
        });
    }
    if (case_name == "point_cloud2") {
        return EncodeCase(path, MakePointCloud2(), [](const auto& value, auto& payload) {
            return hako_convert_cpp2cdr_PointCloud2(value, payload);
        });
    }
    if (case_name == "simple_struct_varray") {
        return EncodeCase(path, MakeSimpleStructVarray(), [](const auto& value, auto& payload) {
            return hako_convert_cpp2cdr_SimpleStructVarray(value, payload);
        });
    }
    std::cerr << "unknown case: " << case_name << std::endl;
    return 1;
}

int Decode(const std::string& case_name, const std::string& path)
{
    if (case_name == "game_controller_operation") {
        return DecodeCase<HakoCpp_GameControllerOperation>(path, [](const auto& payload, auto& value) {
            return hako_convert_cdr2cpp_GameControllerOperation(payload, value);
        });
    }
    if (case_name == "joint_state") {
        return DecodeCase<HakoCpp_JointState>(path, [](const auto& payload, auto& value) {
            return hako_convert_cdr2cpp_JointState(payload, value);
        });
    }
    if (case_name == "point_cloud2") {
        return DecodeCase<HakoCpp_PointCloud2>(path, [](const auto& payload, auto& value) {
            return hako_convert_cdr2cpp_PointCloud2(payload, value);
        });
    }
    if (case_name == "simple_struct_varray") {
        return DecodeCase<HakoCpp_SimpleStructVarray>(path, [](const auto& payload, auto& value) {
            return hako_convert_cdr2cpp_SimpleStructVarray(payload, value);
        });
    }
    std::cerr << "unknown case: " << case_name << std::endl;
    return 1;
}

}  // namespace

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "usage: cdr_oracle_tool <encode|decode> <case> <payload_path>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];
    const std::string case_name = argv[2];
    const std::string path = argv[3];

    if (command == "encode") {
        return Encode(case_name, path);
    }
    if (command == "decode") {
        return Decode(case_name, path);
    }

    std::cerr << "unknown command: " << command << std::endl;
    return 1;
}
