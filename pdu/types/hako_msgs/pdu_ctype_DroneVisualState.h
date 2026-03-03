#ifndef _pdu_ctype_hako_msgs_DroneVisualState_H_
#define _pdu_ctype_hako_msgs_DroneVisualState_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_float32 x;
        Hako_float32 y;
        Hako_float32 z;
        Hako_float32 roll;
        Hako_float32 pitch;
        Hako_float32 yaw;
        // float32 pwm_duty[]
        int _pwm_duty_len;
        int _pwm_duty_off;
} Hako_DroneVisualState;

#endif /* _pdu_ctype_hako_msgs_DroneVisualState_H_ */
