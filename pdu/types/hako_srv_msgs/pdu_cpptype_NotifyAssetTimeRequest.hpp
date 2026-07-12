#ifndef _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_srv_msgs/pdu_cpptype_LogicalTime.hpp"

typedef struct {
        Hako_uint64 session_id;
        HakoCpp_LogicalTime asset_time;
} HakoCpp_NotifyAssetTimeRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_NotifyAssetTimeRequest_HPP_ */
