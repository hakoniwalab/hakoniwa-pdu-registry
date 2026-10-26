#ifndef _pdu_ctype_hako_srv_msgs_AckermannStepRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_AckermannStepRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "ackermann_msgs/pdu_ctype_AckermannDrive.h"
#include "hako_srv_msgs/pdu_ctype_AckermannStepRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_AckermannStepRequest body;
} Hako_AckermannStepRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_AckermannStepRequestPacket_H_ */
