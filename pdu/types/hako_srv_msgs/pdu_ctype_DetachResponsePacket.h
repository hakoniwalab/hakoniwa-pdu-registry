#ifndef _pdu_ctype_hako_srv_msgs_DetachResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_DetachResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_DetachResponse.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_DetachResponse body;
} Hako_DetachResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_DetachResponsePacket_H_ */
