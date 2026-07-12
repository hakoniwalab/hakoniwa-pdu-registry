#ifndef _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_LogicalTime.hpp"
#include "hako_srv_msgs/pdu_cpptype_NotifyAssetTimeRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_NotifyAssetTimeRequest body;
} HakoCpp_NotifyAssetTimeRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequestPacket_HPP_ */
