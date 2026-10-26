#ifndef _pdu_cpptype_hako_srv_msgs_AckermannStepRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_AckermannStepRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "ackermann_msgs/pdu_cpptype_AckermannDrive.hpp"
#include "hako_srv_msgs/pdu_cpptype_AckermannStepRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_AckermannStepRequest body;
} HakoCpp_AckermannStepRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_AckermannStepRequestPacket_HPP_ */
