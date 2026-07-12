#ifndef _pdu_ctype_hako_srv_msgs_AttachResponse_H_
#define _pdu_ctype_hako_srv_msgs_AttachResponse_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"

typedef struct {
        Hako_uint32 result_code;
        Hako_uint64 session_id;
        Hako_LogicalTime world_time;
        Hako_uint64 delta_asset_tick;
} Hako_AttachResponse;

#endif /* _pdu_ctype_hako_srv_msgs_AttachResponse_H_ */
