#ifndef _pdu_cpptype_sensor_msgs_Range_HPP_
#define _pdu_cpptype_sensor_msgs_Range_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        Hako_uint8 radiation_type;
        Hako_float32 field_of_view;
        Hako_float32 min_range;
        Hako_float32 max_range;
        Hako_float32 range;
} HakoCpp_Range;

#endif /* _pdu_cpptype_sensor_msgs_Range_HPP_ */
