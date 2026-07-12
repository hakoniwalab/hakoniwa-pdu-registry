#ifndef _pdu_cpptype_hako_srv_msgs_AttachResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_AttachResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_AttachResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_LogicalTime.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_AttachResponse body;
} HakoCpp_AttachResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_AttachResponsePacket_HPP_ */
