#ifndef _pdu_cpptype_sensor_msgs_TimeReference_HPP_
#define _pdu_cpptype_sensor_msgs_TimeReference_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_Time time_ref;
        std::string source;
} HakoCpp_TimeReference;

#endif /* _pdu_cpptype_sensor_msgs_TimeReference_HPP_ */
