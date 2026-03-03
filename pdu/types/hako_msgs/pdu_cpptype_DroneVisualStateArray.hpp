#ifndef _pdu_cpptype_hako_msgs_DroneVisualStateArray_HPP_
#define _pdu_cpptype_hako_msgs_DroneVisualStateArray_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "hako_msgs/pdu_cpptype_DroneVisualState.hpp"

typedef struct {
        Hako_uint32 sequence_id;
        Hako_uint32 chunk_index;
        Hako_uint32 chunk_count;
        Hako_uint32 start_index;
        Hako_uint32 valid_count;
        std::vector<HakoCpp_DroneVisualState> drones;
} HakoCpp_DroneVisualStateArray;

#endif /* _pdu_cpptype_hako_msgs_DroneVisualStateArray_HPP_ */
