#ifndef _pdu_cpptype_sensor_msgs_PointCloud_HPP_
#define _pdu_cpptype_sensor_msgs_PointCloud_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point32.hpp"
#include "sensor_msgs/pdu_cpptype_ChannelFloat32.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<HakoCpp_Point32> points;
        std::vector<HakoCpp_ChannelFloat32> channels;
} HakoCpp_PointCloud;

#endif /* _pdu_cpptype_sensor_msgs_PointCloud_HPP_ */
