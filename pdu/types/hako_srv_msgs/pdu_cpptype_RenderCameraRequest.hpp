#ifndef _pdu_cpptype_hako_srv_msgs_RenderCameraRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderCameraRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"

typedef struct {
        std::string camera_name;
        Hako_uint64 sim_time_usec;
        HakoCpp_Pose camera_pose;
} HakoCpp_RenderCameraRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderCameraRequest_HPP_ */
