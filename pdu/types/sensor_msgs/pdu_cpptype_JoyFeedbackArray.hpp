#ifndef _pdu_cpptype_sensor_msgs_JoyFeedbackArray_HPP_
#define _pdu_cpptype_sensor_msgs_JoyFeedbackArray_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "sensor_msgs/pdu_cpptype_JoyFeedback.hpp"

typedef struct {
        std::vector<HakoCpp_JoyFeedback> array;
} HakoCpp_JoyFeedbackArray;

#endif /* _pdu_cpptype_sensor_msgs_JoyFeedbackArray_HPP_ */
