#ifndef _pdu_cpptype_hako_srv_msgs_RenderCameraRequestPacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderCameraRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "hako_srv_msgs/pdu_cpptype_RenderCameraRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

typedef struct {
        HakoCpp_ServiceRequestHeader header;
        HakoCpp_RenderCameraRequest body;
} HakoCpp_RenderCameraRequestPacket;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderCameraRequestPacket_HPP_ */
