#ifndef _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "sensor_msgs/pdu_cpptype_Image.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        HakoCpp_Image rgb;
        HakoCpp_Image depth;
        HakoCpp_Image segmentation;
} HakoCpp_RenderCameraFrameResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderCameraFrameResponse_HPP_ */
