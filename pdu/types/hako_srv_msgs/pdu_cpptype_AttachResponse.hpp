#ifndef _pdu_cpptype_hako_srv_msgs_AttachResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_AttachResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_LogicalTime.hpp"

typedef struct {
        Hako_uint32 result_code;
        Hako_uint64 session_id;
        HakoCpp_LogicalTime world_time;
        Hako_uint64 delta_asset_tick;
} HakoCpp_AttachResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_AttachResponse_HPP_ */
