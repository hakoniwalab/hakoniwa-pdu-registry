#ifndef _pdu_cpptype_hako_msgs_ContactEventArray_HPP_
#define _pdu_cpptype_hako_msgs_ContactEventArray_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "hako_msgs/pdu_cpptype_ContactEvent.hpp"

typedef struct {
        std::vector<HakoCpp_ContactEvent> events;
} HakoCpp_ContactEventArray;

#endif /* _pdu_cpptype_hako_msgs_ContactEventArray_HPP_ */
