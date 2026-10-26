#ifndef _pdu_cpptype_hako_srv_msgs_PersonStepRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_PersonStepRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        Hako_uint64 step;
        HakoCpp_Twist cmd_vel;
        std::string animation;
        std::string ride;
} HakoCpp_PersonStepRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_PersonStepRequest_HPP_ */
