#ifndef _pdu_cpptype_hako_srv_msgs_SetLightResponse_HPP_
#define _pdu_cpptype_hako_srv_msgs_SetLightResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>

typedef struct {
        Hako_uint32 result_code;
        std::string message;
} HakoCpp_SetLightResponse;

#endif /* _pdu_cpptype_hako_srv_msgs_SetLightResponse_HPP_ */
