#ifndef _pdu_cpptype_hako_msgs_LightState_HPP_
#define _pdu_cpptype_hako_msgs_LightState_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        std::string source;
        Hako_uint8 mode;
        Hako_float64 luminous_intensity_scale;
        Hako_bool is_lit;
} HakoCpp_LightState;

#endif /* _pdu_cpptype_hako_msgs_LightState_HPP_ */
