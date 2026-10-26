#ifndef _pdu_ctype_hako_msgs_LightState_H_
#define _pdu_ctype_hako_msgs_LightState_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        char source[HAKO_STRING_SIZE];
        Hako_uint8 mode;
        Hako_float64 luminous_intensity_scale;
        Hako_bool is_lit;
} Hako_LightState;

#endif /* _pdu_ctype_hako_msgs_LightState_H_ */
