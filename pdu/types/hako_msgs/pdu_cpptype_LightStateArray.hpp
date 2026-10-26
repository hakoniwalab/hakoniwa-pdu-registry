#ifndef _pdu_cpptype_hako_msgs_LightStateArray_HPP_
#define _pdu_cpptype_hako_msgs_LightStateArray_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_msgs/pdu_cpptype_LightState.hpp"

typedef struct {
        Hako_uint64 stamp_usec;
        std::string carrier;
        std::vector<HakoCpp_LightState> lights;
} HakoCpp_LightStateArray;

#endif /* _pdu_cpptype_hako_msgs_LightStateArray_HPP_ */
