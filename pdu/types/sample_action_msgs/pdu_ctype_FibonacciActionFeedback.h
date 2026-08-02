#ifndef _pdu_ctype_sample_action_msgs_FibonacciActionFeedback_H_
#define _pdu_ctype_sample_action_msgs_FibonacciActionFeedback_H_

#include "pdu_primitive_ctypes.h"
#include "hako_action_msgs/pdu_ctype_ActionFeedbackHeader.h"
#include "sample_action_msgs/pdu_ctype_FibonacciFeedback.h"

typedef struct {
        Hako_ActionFeedbackHeader header;
        Hako_FibonacciFeedback body;
} Hako_FibonacciActionFeedback;

#endif /* _pdu_ctype_sample_action_msgs_FibonacciActionFeedback_H_ */
