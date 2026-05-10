#ifndef _pdu_ctype_sensor_msgs_MultiDOFJointState_H_
#define _pdu_ctype_sensor_msgs_MultiDOFJointState_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "geometry_msgs/pdu_ctype_Wrench.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        // string joint_names[]
        int _joint_names_len;
        int _joint_names_off;
        // geometry_msgs/Transform transforms[]
        int _transforms_len;
        int _transforms_off;
        // geometry_msgs/Twist twist[]
        int _twist_len;
        int _twist_off;
        // geometry_msgs/Wrench wrench[]
        int _wrench_len;
        int _wrench_off;
} Hako_MultiDOFJointState;

#endif /* _pdu_ctype_sensor_msgs_MultiDOFJointState_H_ */
