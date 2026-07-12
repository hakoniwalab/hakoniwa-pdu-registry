#ifndef _pdu_ctype_hako_srv_msgs_GetWorldTimeRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_GetWorldTimeRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_GetWorldTimeRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_GetWorldTimeRequest body;
} Hako_GetWorldTimeRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_GetWorldTimeRequestPacket_H_ */
