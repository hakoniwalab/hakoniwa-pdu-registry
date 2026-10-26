#ifndef _pdu_cpptype_hako_srv_msgs_AckermannStepResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_AckermannStepResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "hako_srv_msgs/pdu_cpptype_AckermannStepResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_AckermannStepResponse body;
} HakoCpp_AckermannStepResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_AckermannStepResponsePacket_HPP_ */
