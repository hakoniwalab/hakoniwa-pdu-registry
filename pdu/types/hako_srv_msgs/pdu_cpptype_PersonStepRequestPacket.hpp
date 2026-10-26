#ifndef _pdu_cpptype_hako_srv_msgs_PersonStepRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_PersonStepRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "hako_srv_msgs/pdu_cpptype_PersonStepRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_PersonStepRequest body;
} HakoCpp_PersonStepRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_PersonStepRequestPacket_HPP_ */
