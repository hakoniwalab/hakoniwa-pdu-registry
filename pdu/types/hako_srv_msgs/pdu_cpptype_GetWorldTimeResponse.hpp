#ifndef _pdu_cpptype_hako_srv_msgs_GetWorldTimeResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_GetWorldTimeResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_LogicalTime.hpp"

typedef struct {
        Hako_uint32 result_code;
        HakoCpp_LogicalTime world_time;
} HakoCpp_GetWorldTimeResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_GetWorldTimeResponse_HPP_ */
