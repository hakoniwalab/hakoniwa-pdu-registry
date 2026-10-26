#ifndef _pdu_cpptype_hako_srv_msgs_SetLightRequest_HPP_
#define _pdu_cpptype_hako_srv_msgs_SetLightRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        std::string source;
        Hako_uint8 mode;
        Hako_float64 luminous_intensity_scale;
        Hako_float64 flashing_on_s;
        Hako_float64 flashing_off_s;
        Hako_float64 transition_s;
} HakoCpp_SetLightRequest;

#endif /* _pdu_cpptype_hako_srv_msgs_SetLightRequest_HPP_ */
