#ifndef _pdu_cpptype_hako_srv_msgs_AckermannStepRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_AckermannStepRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "ackermann_msgs/pdu_cpptype_AckermannDrive.hpp"

typedef struct {
        Hako_uint64 step;
        HakoCpp_AckermannDrive drive;
} HakoCpp_AckermannStepRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_AckermannStepRequest_HPP_ */
