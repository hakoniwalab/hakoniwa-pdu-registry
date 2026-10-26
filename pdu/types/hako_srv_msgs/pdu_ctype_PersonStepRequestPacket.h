#ifndef _pdu_ctype_hako_srv_msgs_PersonStepRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_PersonStepRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "hako_srv_msgs/pdu_ctype_PersonStepRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_PersonStepRequest body;
} Hako_PersonStepRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_PersonStepRequestPacket_H_ */
