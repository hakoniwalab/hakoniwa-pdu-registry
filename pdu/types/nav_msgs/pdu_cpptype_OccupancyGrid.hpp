#ifndef _pdu_cpptype_nav_msgs_OccupancyGrid_HPP_
#define _pdu_cpptype_nav_msgs_OccupancyGrid_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "nav_msgs/pdu_cpptype_MapMetaData.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_MapMetaData info;
        std::vector<Hako_int8> data;
} HakoCpp_OccupancyGrid;

#endif /* _pdu_cpptype_nav_msgs_OccupancyGrid_HPP_ */
