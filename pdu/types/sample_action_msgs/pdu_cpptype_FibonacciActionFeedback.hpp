#ifndef _pdu_cpptype_sample_action_msgs_FibonacciActionFeedback_HPP_
#define _pdu_cpptype_sample_action_msgs_FibonacciActionFeedback_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_action_msgs/pdu_cpptype_ActionFeedbackHeader.hpp"
#include "sample_action_msgs/pdu_cpptype_FibonacciFeedback.hpp"

typedef struct {
        HakoCpp_ActionFeedbackHeader header;
        HakoCpp_FibonacciFeedback body;
} HakoCpp_FibonacciActionFeedback;

#endif /* _pdu_cpptype_sample_action_msgs_FibonacciActionFeedback_HPP_ */
