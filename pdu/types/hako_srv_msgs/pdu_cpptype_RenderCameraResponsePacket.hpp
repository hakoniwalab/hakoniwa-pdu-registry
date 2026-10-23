#ifndef _pdu_cpptype_hako_srv_msgs_RenderCameraResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderCameraResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "hako_srv_msgs/pdu_cpptype_RenderCameraResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"
#include "sensor_msgs/pdu_cpptype_Image.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_RenderCameraResponse body;
} HakoCpp_RenderCameraResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderCameraResponsePacket_HPP_ */
