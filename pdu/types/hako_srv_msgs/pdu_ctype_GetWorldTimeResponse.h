#ifndef _pdu_ctype_hako_srv_msgs_GetWorldTimeResponse_H_
#define _pdu_ctype_hako_srv_msgs_GetWorldTimeResponse_H_

#include "pdu_primitive_ctypes.h"
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"

typedef struct {
        Hako_uint32 result_code;
        Hako_LogicalTime world_time;
} Hako_GetWorldTimeResponse;

#endif /* _pdu_ctype_hako_srv_msgs_GetWorldTimeResponse_H_ */
