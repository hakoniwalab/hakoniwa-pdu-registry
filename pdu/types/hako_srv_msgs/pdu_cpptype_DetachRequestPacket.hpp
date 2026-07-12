#ifndef _pdu_cpptype_hako_srv_msgs_DetachRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_DetachRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_DetachRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_DetachRequest body;
} HakoCpp_DetachRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_DetachRequestPacket_HPP_ */
