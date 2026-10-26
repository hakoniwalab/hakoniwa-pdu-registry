#ifndef _pdu_ctype_hako_srv_msgs_SetLightResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_SetLightResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"
#include "hako_srv_msgs/pdu_ctype_SetLightResponse.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_SetLightResponse body;
} Hako_SetLightResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_SetLightResponsePacket_H_ */
