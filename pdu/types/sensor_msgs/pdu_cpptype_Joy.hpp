#ifndef _pdu_cpptype_sensor_msgs_Joy_HPP_
#define _pdu_cpptype_sensor_msgs_Joy_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<Hako_float32> axes;
        std::vector<Hako_int32> buttons;
} HakoCpp_Joy;

#endif /* _pdu_cpptype_sensor_msgs_Joy_HPP_ */
