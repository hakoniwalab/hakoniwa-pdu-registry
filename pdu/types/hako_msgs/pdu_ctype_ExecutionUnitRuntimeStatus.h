#ifndef _pdu_ctype_hako_msgs_ExecutionUnitRuntimeStatus_H_
#define _pdu_ctype_hako_msgs_ExecutionUnitRuntimeStatus_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint32 config_hash;
        Hako_uint16 unit_count;
        // uint8 status[]
        int _status_len;
        int _status_off;
        // uint8 epoch[]
        int _epoch_len;
        int _epoch_off;
        // uint8 curr_owner_node_id[]
        int _curr_owner_node_id_len;
        int _curr_owner_node_id_off;
        // uint8 next_owner_node_id[]
        int _next_owner_node_id_len;
        int _next_owner_node_id_off;
} Hako_ExecutionUnitRuntimeStatus;

#endif /* _pdu_ctype_hako_msgs_ExecutionUnitRuntimeStatus_H_ */
