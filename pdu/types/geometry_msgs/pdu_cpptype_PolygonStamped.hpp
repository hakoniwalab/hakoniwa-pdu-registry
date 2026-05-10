#ifndef _pdu_cpptype_geometry_msgs_PolygonStamped_HPP_
#define _pdu_cpptype_geometry_msgs_PolygonStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point32.hpp"
#include "geometry_msgs/pdu_cpptype_Polygon.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_Polygon polygon;
} HakoCpp_PolygonStamped;

#endif /* _pdu_cpptype_geometry_msgs_PolygonStamped_HPP_ */
