#ifndef _pdu_ctype_hako_srv_msgs_AttachRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_AttachRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_AttachRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_AttachRequest body;
} Hako_AttachRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_AttachRequestPacket_H_ */
