#ifndef _pdu_ctype_sensor_msgs_ChannelFloat32_H_
#define _pdu_ctype_sensor_msgs_ChannelFloat32_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        char name[HAKO_STRING_SIZE];
        // float32 values[]
        int _values_len;
        int _values_off;
} Hako_ChannelFloat32;

#endif /* _pdu_ctype_sensor_msgs_ChannelFloat32_H_ */
