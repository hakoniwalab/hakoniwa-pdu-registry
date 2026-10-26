#ifndef _pdu_cpptype_hako_srv_msgs_SetLightRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_SetLightRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"
#include "hako_srv_msgs/pdu_cpptype_SetLightRequest.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_SetLightRequest body;
} HakoCpp_SetLightRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_SetLightRequestPacket_HPP_ */
