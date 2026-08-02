#ifndef _pdu_ctype_hako_action_msgs_ActionResponseHeader_H_
#define _pdu_ctype_hako_action_msgs_ActionResponseHeader_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint8 version;
        Hako_uint8 response_kind;
        Hako_uint8 status;
        Hako_uint8 reserved;
        Hako_uint8 goal_id[16];
} Hako_ActionResponseHeader;

#endif /* _pdu_ctype_hako_action_msgs_ActionResponseHeader_H_ */
