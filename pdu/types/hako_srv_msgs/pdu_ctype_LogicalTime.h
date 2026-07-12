#ifndef _pdu_ctype_hako_srv_msgs_LogicalTime_H_
#define _pdu_ctype_hako_srv_msgs_LogicalTime_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint64 generation;
        Hako_uint64 offset_tick;
} Hako_LogicalTime;

#endif /* _pdu_ctype_hako_srv_msgs_LogicalTime_H_ */
