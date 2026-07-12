#ifndef _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequest_H_
#define _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequest_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"

typedef struct {
        Hako_uint64 session_id;
        Hako_LogicalTime asset_time;
} Hako_NotifyAssetTimeRequest;

#endif /* _pdu_ctype_hako_srv_msgs_NotifyAssetTimeRequest_H_ */
