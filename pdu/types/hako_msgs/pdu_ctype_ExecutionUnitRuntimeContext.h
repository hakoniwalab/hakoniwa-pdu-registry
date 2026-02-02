#ifndef _pdu_ctype_hako_msgs_ExecutionUnitRuntimeContext_H_
#define _pdu_ctype_hako_msgs_ExecutionUnitRuntimeContext_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint32 config_hash;
        Hako_uint8 epoch;
        Hako_uint8 owner_id;
        // uint8 context[]
        int _context_len;
        int _context_off;
} Hako_ExecutionUnitRuntimeContext;

#endif /* _pdu_ctype_hako_msgs_ExecutionUnitRuntimeContext_H_ */
