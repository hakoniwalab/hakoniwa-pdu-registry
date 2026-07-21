#ifndef _pdu_cpptype_trajectory_msgs_JointTrajectoryPoint_HPP_
#define _pdu_cpptype_trajectory_msgs_JointTrajectoryPoint_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Duration.hpp"

typedef struct {
        std::vector<Hako_float64> positions;
        std::vector<Hako_float64> velocities;
        std::vector<Hako_float64> accelerations;
        std::vector<Hako_float64> effort;
        HakoCpp_Duration time_from_start;
} HakoCpp_JointTrajectoryPoint;

#endif /* _pdu_cpptype_trajectory_msgs_JointTrajectoryPoint_HPP_ */
