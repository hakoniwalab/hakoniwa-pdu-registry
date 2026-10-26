#ifndef _pdu_cpptype_hako_srv_msgs_SetLightResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_SetLightResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"
#include "hako_srv_msgs/pdu_cpptype_SetLightResponse.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_SetLightResponse body;
} HakoCpp_SetLightResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_SetLightResponsePacket_HPP_ */
