#ifndef _pdu_ctype_hako_srv_msgs_GetWorldTimeResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_GetWorldTimeResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_GetWorldTimeResponse.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_GetWorldTimeResponse body;
} Hako_GetWorldTimeResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_GetWorldTimeResponsePacket_H_ */
