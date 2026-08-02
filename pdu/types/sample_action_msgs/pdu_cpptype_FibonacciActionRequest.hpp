#ifndef _pdu_cpptype_sample_action_msgs_FibonacciActionRequest_HPP_
#define _pdu_cpptype_sample_action_msgs_FibonacciActionRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_action_msgs/pdu_cpptype_ActionRequestHeader.hpp"
#include "sample_action_msgs/pdu_cpptype_FibonacciGoal.hpp"

typedef struct {
        HakoCpp_ActionRequestHeader header;
        HakoCpp_FibonacciGoal body;
} HakoCpp_FibonacciActionRequest;

#endif /* _pdu_cpptype_sample_action_msgs_FibonacciActionRequest_HPP_ */
