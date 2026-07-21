#ifndef _pdu_cpptype_trajectory_msgs_JointTrajectory_HPP_
#define _pdu_cpptype_trajectory_msgs_JointTrajectory_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Duration.hpp"
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"
#include "trajectory_msgs/pdu_cpptype_JointTrajectoryPoint.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<std::string> joint_names;
        std::vector<HakoCpp_JointTrajectoryPoint> points;
} HakoCpp_JointTrajectory;

#endif /* _pdu_cpptype_trajectory_msgs_JointTrajectory_HPP_ */
