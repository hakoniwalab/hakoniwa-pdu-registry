#ifndef _pdu_cpptype_sensor_msgs_JoyFeedback_HPP_
#define _pdu_cpptype_sensor_msgs_JoyFeedback_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint8 type;
        Hako_uint8 id;
        Hako_float32 intensity;
} HakoCpp_JoyFeedback;

#endif /* _pdu_cpptype_sensor_msgs_JoyFeedback_HPP_ */
