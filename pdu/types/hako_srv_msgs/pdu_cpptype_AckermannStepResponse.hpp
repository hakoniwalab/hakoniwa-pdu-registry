#ifndef _pdu_cpptype_hako_srv_msgs_AckermannStepResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_AckermannStepResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        Hako_uint64 step;
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        HakoCpp_Transform pose;
        HakoCpp_Twist twist;
} HakoCpp_AckermannStepResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_AckermannStepResponse_HPP_ */
