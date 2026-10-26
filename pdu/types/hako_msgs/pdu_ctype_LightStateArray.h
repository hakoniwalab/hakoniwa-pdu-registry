#ifndef _pdu_ctype_hako_msgs_LightStateArray_H_
#define _pdu_ctype_hako_msgs_LightStateArray_H_

#include "pdu_primitive_ctypes.h"
#include "hako_msgs/pdu_ctype_LightState.h"

typedef struct {
        Hako_uint64 stamp_usec;
        char carrier[HAKO_STRING_SIZE];
        // LightState lights[]
        int _lights_len;
        int _lights_off;
} Hako_LightStateArray;

#endif /* _pdu_ctype_hako_msgs_LightStateArray_H_ */
