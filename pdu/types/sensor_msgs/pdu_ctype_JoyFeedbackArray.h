#ifndef _pdu_ctype_sensor_msgs_JoyFeedbackArray_H_
#define _pdu_ctype_sensor_msgs_JoyFeedbackArray_H_

#include "pdu_primitive_ctypes.h"
#include "sensor_msgs/pdu_ctype_JoyFeedback.h"

typedef struct {
        // JoyFeedback array[]
        int _array_len;
        int _array_off;
} Hako_JoyFeedbackArray;

#endif /* _pdu_ctype_sensor_msgs_JoyFeedbackArray_H_ */
