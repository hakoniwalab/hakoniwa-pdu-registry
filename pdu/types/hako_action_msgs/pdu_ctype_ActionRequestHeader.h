#ifndef _pdu_ctype_hako_action_msgs_ActionRequestHeader_H_
#define _pdu_ctype_hako_action_msgs_ActionRequestHeader_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint8 version;
        Hako_uint8 request_kind;
        Hako_uint8 reserved[2];
        Hako_uint8 goal_id[16];
} Hako_ActionRequestHeader;

#endif /* _pdu_ctype_hako_action_msgs_ActionRequestHeader_H_ */
