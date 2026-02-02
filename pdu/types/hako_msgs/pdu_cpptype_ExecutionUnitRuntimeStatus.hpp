#ifndef _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeStatus_HPP_
#define _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeStatus_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint32 config_hash;
        Hako_uint16 unit_count;
        std::vector<Hako_uint8> status;
        std::vector<Hako_uint8> epoch;
        std::vector<Hako_uint8> curr_owner_node_id;
        std::vector<Hako_uint8> next_owner_node_id;
} HakoCpp_ExecutionUnitRuntimeStatus;

#endif /* _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeStatus_HPP_ */
