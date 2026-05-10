#ifndef _pdu_cpptype_geometry_msgs_Inertia_HPP_
#define _pdu_cpptype_geometry_msgs_Inertia_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        Hako_float64 m;
        HakoCpp_Vector3 com;
        Hako_float64 ixx;
        Hako_float64 ixy;
        Hako_float64 ixz;
        Hako_float64 iyy;
        Hako_float64 iyz;
        Hako_float64 izz;
} HakoCpp_Inertia;

#endif /* _pdu_cpptype_geometry_msgs_Inertia_HPP_ */
