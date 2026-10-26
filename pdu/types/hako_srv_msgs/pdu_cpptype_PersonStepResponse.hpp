#ifndef _pdu_cpptype_hako_srv_msgs_PersonStepResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_PersonStepResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "sensor_msgs/pdu_cpptype_JointState.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        Hako_uint64 step;
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        HakoCpp_Transform pose;
        HakoCpp_Twist twist;
        HakoCpp_JointState joints;
} HakoCpp_PersonStepResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_PersonStepResponse_HPP_ */
