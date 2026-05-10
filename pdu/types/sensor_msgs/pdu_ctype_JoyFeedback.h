#ifndef _pdu_ctype_sensor_msgs_JoyFeedback_H_
#define _pdu_ctype_sensor_msgs_JoyFeedback_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint8 type;
        Hako_uint8 id;
        Hako_float32 intensity;
} Hako_JoyFeedback;

#endif /* _pdu_ctype_sensor_msgs_JoyFeedback_H_ */
