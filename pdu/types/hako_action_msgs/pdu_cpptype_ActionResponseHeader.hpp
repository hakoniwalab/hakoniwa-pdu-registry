#ifndef _pdu_cpptype_hako_action_msgs_ActionResponseHeader_HPP_
#define _pdu_cpptype_hako_action_msgs_ActionResponseHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint8 version;
        Hako_uint8 response_kind;
        Hako_uint8 status;
        Hako_uint8 reserved;
        std::array<Hako_uint8, 16> goal_id;
} HakoCpp_ActionResponseHeader;

#endif /* _pdu_cpptype_hako_action_msgs_ActionResponseHeader_HPP_ */
