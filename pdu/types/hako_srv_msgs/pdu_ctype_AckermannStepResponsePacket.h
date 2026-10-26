#ifndef _pdu_ctype_hako_srv_msgs_AckermannStepResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_AckermannStepResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "hako_srv_msgs/pdu_ctype_AckermannStepResponse.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_AckermannStepResponse body;
} Hako_AckermannStepResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_AckermannStepResponsePacket_H_ */
