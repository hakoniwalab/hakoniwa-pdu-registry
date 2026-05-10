#ifndef _pdu_cpptype_nav_msgs_Path_HPP_
#define _pdu_cpptype_nav_msgs_Path_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_PoseStamped.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<HakoCpp_PoseStamped> poses;
} HakoCpp_Path;

#endif /* _pdu_cpptype_nav_msgs_Path_HPP_ */
