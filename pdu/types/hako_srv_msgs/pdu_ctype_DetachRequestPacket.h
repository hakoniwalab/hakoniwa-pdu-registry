#ifndef _pdu_ctype_hako_srv_msgs_DetachRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_DetachRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_DetachRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_DetachRequest body;
} Hako_DetachRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_DetachRequestPacket_H_ */
