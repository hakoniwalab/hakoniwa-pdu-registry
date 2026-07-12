#ifndef _pdu_cpptype_hako_srv_msgs_GetWorldTimeRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_GetWorldTimeRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_GetWorldTimeRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_GetWorldTimeRequest body;
} HakoCpp_GetWorldTimeRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_GetWorldTimeRequestPacket_HPP_ */
