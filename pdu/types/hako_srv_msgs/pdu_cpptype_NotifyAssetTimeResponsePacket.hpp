#ifndef _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_NotifyAssetTimeResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_NotifyAssetTimeResponse body;
} HakoCpp_NotifyAssetTimeResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_ */
