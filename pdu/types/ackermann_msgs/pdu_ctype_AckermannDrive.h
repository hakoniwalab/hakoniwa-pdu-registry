#ifndef _pdu_ctype_ackermann_msgs_AckermannDrive_H_
#define _pdu_ctype_ackermann_msgs_AckermannDrive_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_float32 steering_angle;
        Hako_float32 steering_angle_velocity;
        Hako_float32 speed;
        Hako_float32 acceleration;
        Hako_float32 jerk;
} Hako_AckermannDrive;

#endif /* _pdu_ctype_ackermann_msgs_AckermannDrive_H_ */
