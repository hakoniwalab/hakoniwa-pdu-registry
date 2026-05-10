#ifndef _pdu_cpptype_geometry_msgs_Polygon_HPP_
#define _pdu_cpptype_geometry_msgs_Polygon_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Point32.hpp"

typedef struct {
        std::vector<HakoCpp_Point32> points;
} HakoCpp_Polygon;

#endif /* _pdu_cpptype_geometry_msgs_Polygon_HPP_ */
