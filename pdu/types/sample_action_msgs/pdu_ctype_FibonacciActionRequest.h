#ifndef _pdu_ctype_sample_action_msgs_FibonacciActionRequest_H_
#define _pdu_ctype_sample_action_msgs_FibonacciActionRequest_H_

#include "pdu_primitive_ctypes.h"
#include "hako_action_msgs/pdu_ctype_ActionRequestHeader.h"
#include "sample_action_msgs/pdu_ctype_FibonacciGoal.h"

typedef struct {
        Hako_ActionRequestHeader header;
        Hako_FibonacciGoal body;
} Hako_FibonacciActionRequest;

#endif /* _pdu_ctype_sample_action_msgs_FibonacciActionRequest_H_ */
