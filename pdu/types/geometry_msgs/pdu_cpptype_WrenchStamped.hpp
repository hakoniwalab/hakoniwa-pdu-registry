#ifndef _pdu_cpptype_geometry_msgs_WrenchStamped_HPP_
#define _pdu_cpptype_geometry_msgs_WrenchStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "geometry_msgs/pdu_cpptype_Wrench.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_Wrench wrench;
} HakoCpp_WrenchStamped;

#endif /* _pdu_cpptype_geometry_msgs_WrenchStamped_HPP_ */
