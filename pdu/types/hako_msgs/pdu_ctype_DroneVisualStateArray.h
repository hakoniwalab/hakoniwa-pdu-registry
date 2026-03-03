#ifndef _pdu_ctype_hako_msgs_DroneVisualStateArray_H_
#define _pdu_ctype_hako_msgs_DroneVisualStateArray_H_

#include "pdu_primitive_ctypes.h"
#include "hako_msgs/pdu_ctype_DroneVisualState.h"

typedef struct {
        Hako_uint32 sequence_id;
        Hako_uint32 chunk_index;
        Hako_uint32 chunk_count;
        Hako_uint32 start_index;
        Hako_uint32 valid_count;
        // hako_msgs/DroneVisualState drones[]
        int _drones_len;
        int _drones_off;
} Hako_DroneVisualStateArray;

#endif /* _pdu_ctype_hako_msgs_DroneVisualStateArray_H_ */
