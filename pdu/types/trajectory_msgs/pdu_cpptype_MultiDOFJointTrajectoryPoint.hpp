#ifndef _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_
#define _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Duration.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        std::vector<HakoCpp_Transform> transforms;
        std::vector<HakoCpp_Twist> velocities;
        std::vector<HakoCpp_Twist> accelerations;
        HakoCpp_Duration time_from_start;
} HakoCpp_MultiDOFJointTrajectoryPoint;

#endif /* _pdu_cpptype_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_ */
