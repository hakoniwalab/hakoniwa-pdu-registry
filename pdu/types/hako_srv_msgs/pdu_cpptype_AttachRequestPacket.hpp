#ifndef _pdu_cpptype_hako_srv_msgs_AttachRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_AttachRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_AttachRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_AttachRequest body;
} HakoCpp_AttachRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_AttachRequestPacket_HPP_ */
