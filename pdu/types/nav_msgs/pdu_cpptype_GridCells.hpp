#ifndef _pdu_cpptype_nav_msgs_GridCells_HPP_
#define _pdu_cpptype_nav_msgs_GridCells_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        Hako_float32 cell_width;
        Hako_float32 cell_height;
        std::vector<HakoCpp_Point> cells;
} HakoCpp_GridCells;

#endif /* _pdu_cpptype_nav_msgs_GridCells_HPP_ */
