#ifndef _pdu_ctype_hako_action_msgs_ActionFeedbackHeader_H_
#define _pdu_ctype_hako_action_msgs_ActionFeedbackHeader_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint8 version;
        Hako_uint8 reserved[3];
        Hako_uint8 goal_id[16];
        Hako_uint32 sequence_no;
} Hako_ActionFeedbackHeader;

#endif /* _pdu_ctype_hako_action_msgs_ActionFeedbackHeader_H_ */
