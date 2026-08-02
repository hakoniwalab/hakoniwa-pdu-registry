#ifndef _pdu_cpptype_hako_action_msgs_ActionFeedbackHeader_HPP_
#define _pdu_cpptype_hako_action_msgs_ActionFeedbackHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint8 version;
        std::array<Hako_uint8, 3> reserved;
        std::array<Hako_uint8, 16> goal_id;
        Hako_uint32 sequence_no;
} HakoCpp_ActionFeedbackHeader;

#endif /* _pdu_cpptype_hako_action_msgs_ActionFeedbackHeader_HPP_ */
