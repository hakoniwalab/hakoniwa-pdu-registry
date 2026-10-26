#ifndef _pdu_ctype_hako_srv_msgs_SetLightRequest_H_
#define _pdu_ctype_hako_srv_msgs_SetLightRequest_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        char source[HAKO_STRING_SIZE];
        Hako_uint8 mode;
        Hako_float64 luminous_intensity_scale;
        Hako_float64 flashing_on_s;
        Hako_float64 flashing_off_s;
        Hako_float64 transition_s;
} Hako_SetLightRequest;

#endif /* _pdu_ctype_hako_srv_msgs_SetLightRequest_H_ */
