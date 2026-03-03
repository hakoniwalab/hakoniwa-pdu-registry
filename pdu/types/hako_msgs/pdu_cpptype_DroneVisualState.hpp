#ifndef _pdu_cpptype_hako_msgs_DroneVisualState_HPP_
#define _pdu_cpptype_hako_msgs_DroneVisualState_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_float32 x;
        Hako_float32 y;
        Hako_float32 z;
        Hako_float32 roll;
        Hako_float32 pitch;
        Hako_float32 yaw;
        std::vector<Hako_float32> pwm_duty;
} HakoCpp_DroneVisualState;

#endif /* _pdu_cpptype_hako_msgs_DroneVisualState_HPP_ */
