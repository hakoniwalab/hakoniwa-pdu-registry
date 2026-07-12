#ifndef _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"
#include "hako_srv_msgs/pdu_ctype_NotifyAssetTimeRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_NotifyAssetTimeRequest body;
} Hako_NotifyAssetTimeRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequestPacket_H_ */
