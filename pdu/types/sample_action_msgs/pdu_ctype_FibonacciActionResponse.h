#ifndef _pdu_ctype_sample_action_msgs_FibonacciActionResponse_H_
#define _pdu_ctype_sample_action_msgs_FibonacciActionResponse_H_

#include "pdu_primitive_ctypes.h"
#include "hako_action_msgs/pdu_ctype_ActionResponseHeader.h"
#include "sample_action_msgs/pdu_ctype_FibonacciResult.h"

typedef struct {
        Hako_ActionResponseHeader header;
        Hako_FibonacciResult body;
} Hako_FibonacciActionResponse;

#endif /* _pdu_ctype_sample_action_msgs_FibonacciActionResponse_H_ */
