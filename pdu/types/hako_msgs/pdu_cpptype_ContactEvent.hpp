#ifndef _pdu_cpptype_hako_msgs_ContactEvent_HPP_
#define _pdu_cpptype_hako_msgs_ContactEvent_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"

typedef struct {
        HakoCpp_Time stamp;
        std::string self_name;
        std::string other_name;
        std::string other_kind;
        HakoCpp_Point position;
        Hako_float64 relative_speed;
        Hako_bool started;
} HakoCpp_ContactEvent;

#endif /* _pdu_cpptype_hako_msgs_ContactEvent_HPP_ */
