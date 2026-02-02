#ifndef _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeContext_HPP_
#define _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeContext_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint32 config_hash;
        Hako_uint8 epoch;
        Hako_uint8 owner_id;
        std::vector<Hako_uint8> context;
} HakoCpp_ExecutionUnitRuntimeContext;

#endif /* _pdu_cpptype_hako_msgs_ExecutionUnitRuntimeContext_HPP_ */
