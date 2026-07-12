#ifndef _pdu_cpptype_hako_srv_msgs_AttachRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_AttachRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        std::string asset_name;
        Hako_uint64 delta_asset_tick;
} HakoCpp_AttachRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_AttachRequest_HPP_ */
