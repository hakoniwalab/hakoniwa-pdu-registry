#ifndef _pdu_ctype_hako_srv_msgs_NotifyAssetTimeResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_NotifyAssetTimeResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_NotifyAssetTimeResponse.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_NotifyAssetTimeResponse body;
} Hako_NotifyAssetTimeResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_NotifyAssetTimeResponsePacket_H_ */
