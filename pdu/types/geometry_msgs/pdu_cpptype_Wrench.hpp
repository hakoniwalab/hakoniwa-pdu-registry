#ifndef _pdu_cpptype_geometry_msgs_Wrench_HPP_
#define _pdu_cpptype_geometry_msgs_Wrench_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        HakoCpp_Vector3 force;
        HakoCpp_Vector3 torque;
} HakoCpp_Wrench;

#endif /* _pdu_cpptype_geometry_msgs_Wrench_HPP_ */
