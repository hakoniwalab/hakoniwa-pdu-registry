#ifndef _pdu_cpptype_sensor_msgs_MultiDOFJointState_HPP_
#define _pdu_cpptype_sensor_msgs_MultiDOFJointState_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "geometry_msgs/pdu_cpptype_Wrench.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        std::vector<std::string> joint_names;
        std::vector<HakoCpp_Transform> transforms;
        std::vector<HakoCpp_Twist> twist;
        std::vector<HakoCpp_Wrench> wrench;
} HakoCpp_MultiDOFJointState;

#endif /* _pdu_cpptype_sensor_msgs_MultiDOFJointState_HPP_ */
