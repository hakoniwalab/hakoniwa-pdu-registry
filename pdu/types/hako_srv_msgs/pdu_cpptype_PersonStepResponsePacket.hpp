#ifndef _pdu_cpptype_hako_srv_msgs_PersonStepResponsePacket_HPP_
#define _pdu_cpptype_hako_srv_msgs_PersonStepResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "hako_srv_msgs/pdu_cpptype_PersonStepResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"
#include "sensor_msgs/pdu_cpptype_JointState.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_ServiceResponseHeader header;
        HakoCpp_PersonStepResponse body;
} HakoCpp_PersonStepResponsePacket;

#endif /* _pdu_cpptype_hako_srv_msgs_PersonStepResponsePacket_HPP_ */
