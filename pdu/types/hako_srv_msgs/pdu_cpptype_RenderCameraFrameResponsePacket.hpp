#ifndef _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "hako_srv_msgs/pdu_cpptype_RenderCameraFrameResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"
#include "sensor_msgs/pdu_cpptype_Image.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_RenderCameraFrameResponse body;
} HakoCpp_RenderCameraFrameResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponsePacket_HPP_ */
