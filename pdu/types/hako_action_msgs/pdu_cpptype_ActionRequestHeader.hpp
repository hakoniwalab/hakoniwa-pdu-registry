#ifndef _pdu_cpptype_hako_action_msgs_ActionRequestHeader_HPP_
#define _pdu_cpptype_hako_action_msgs_ActionRequestHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint8 version;
        Hako_uint8 request_kind;
        std::array<Hako_uint8, 2> reserved;
        std::array<Hako_uint8, 16> goal_id;
} HakoCpp_ActionRequestHeader;

#endif /* _pdu_cpptype_hako_action_msgs_ActionRequestHeader_HPP_ */
