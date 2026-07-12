#ifndef _pdu_cpptype_hako_srv_msgs_LogicalTime_HPP_
#define _pdu_cpptype_hako_srv_msgs_LogicalTime_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint64 generation;
        Hako_uint64 offset_tick;
} HakoCpp_LogicalTime;

#endif /* _pdu_cpptype_hako_srv_msgs_LogicalTime_HPP_ */
