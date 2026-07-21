#ifndef _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectory_HPP_
#define _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectory_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Duration.hpp"
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"
#include "trajectory_msgs/pdu_cpptype_MultiDOFJointTrajectoryPoint.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<std::string> joint_names;
        std::vector<HakoCpp_MultiDOFJointTrajectoryPoint> points;
} HakoCpp_MultiDOFJointTrajectory;

#endif /* _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectory_HPP_ */
