#ifndef _pdu_cpptype_nav_msgs_MapMetaData_HPP_
#define _pdu_cpptype_nav_msgs_MapMetaData_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"

typedef struct {
        HakoCpp_Time map_load_time;
        Hako_float32 resolution;
        Hako_uint32 width;
        Hako_uint32 height;
        HakoCpp_Pose origin;
} HakoCpp_MapMetaData;

#endif /* _pdu_cpptype_nav_msgs_MapMetaData_HPP_ */
