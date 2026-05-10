#ifndef _pdu_cpptype_geometry_msgs_PoseWithCovarianceStamped_HPP_
#define _pdu_cpptype_geometry_msgs_PoseWithCovarianceStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_PoseWithCovariance.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_PoseWithCovariance pose;
} HakoCpp_PoseWithCovarianceStamped;

#endif /* _pdu_cpptype_geometry_msgs_PoseWithCovarianceStamped_HPP_ */
