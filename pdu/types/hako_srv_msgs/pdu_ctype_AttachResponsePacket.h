#ifndef _pdu_ctype_hako_srv_msgs_AttachResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_AttachResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_AttachResponse.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_AttachResponse body;
} Hako_AttachResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_AttachResponsePacket_H_ */
