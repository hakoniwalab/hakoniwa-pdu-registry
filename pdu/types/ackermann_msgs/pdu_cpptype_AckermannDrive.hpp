#ifndef _pdu_cpptype_ackermann_msgs_AckermannDrive_HPP_
#define _pdu_cpptype_ackermann_msgs_AckermannDrive_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_float32 steering_angle;
        Hako_float32 steering_angle_velocity;
        Hako_float32 speed;
        Hako_float32 acceleration;
        Hako_float32 jerk;
} HakoCpp_AckermannDrive;

#endif /* _pdu_cpptype_ackermann_msgs_AckermannDrive_HPP_ */
