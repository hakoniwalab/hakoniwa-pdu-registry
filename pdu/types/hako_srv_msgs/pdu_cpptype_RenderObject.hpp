#ifndef _pdu_cpptype_hako_srv_msgs_RenderObject_HPP_
#define _pdu_cpptype_hako_srv_msgs_RenderObject_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Point.hpp"
#include "geometry_msgs/pdu_cpptype_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"

typedef struct {
        std::string name;
        std::string model;
        HakoCpp_Pose pose;
} HakoCpp_RenderObject;

#endif /* _pdu_cpptype_hako_srv_msgs_RenderObject_HPP_ */
