#ifndef _pdu_cpptype_sample_action_msgs_FibonacciActionResponse_HPP_
#define _pdu_cpptype_sample_action_msgs_FibonacciActionResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_action_msgs/pdu_cpptype_ActionResponseHeader.hpp"
#include "sample_action_msgs/pdu_cpptype_FibonacciResult.hpp"

typedef struct {
        HakoCpp_ActionResponseHeader header;
        HakoCpp_FibonacciResult body;
} HakoCpp_FibonacciActionResponse;

#endif /* _pdu_cpptype_sample_action_msgs_FibonacciActionResponse_HPP_ */
