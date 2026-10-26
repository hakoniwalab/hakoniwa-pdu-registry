#ifndef _pdu_ctype_hako_srv_msgs_PersonStepResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_PersonStepResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "hako_srv_msgs/pdu_ctype_PersonStepResponse.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"
#include "sensor_msgs/pdu_ctype_JointState.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_PersonStepResponse body;
} Hako_PersonStepResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_PersonStepResponsePacket_H_ */
