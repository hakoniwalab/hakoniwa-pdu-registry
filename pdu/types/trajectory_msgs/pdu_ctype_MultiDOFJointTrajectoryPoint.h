#ifndef _pdu_ctype_trajectory_msgs_MultiDOFJointTrajectoryPoint_H_
#define _pdu_ctype_trajectory_msgs_MultiDOFJointTrajectoryPoint_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Duration.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        // geometry_msgs/Transform transforms[]
        int _transforms_len;
        int _transforms_off;
        // geometry_msgs/Twist velocities[]
        int _velocities_len;
        int _velocities_off;
        // geometry_msgs/Twist accelerations[]
        int _accelerations_len;
        int _accelerations_off;
        Hako_Duration time_from_start;
} Hako_MultiDOFJointTrajectoryPoint;

#endif /* _pdu_ctype_trajectory_msgs_MultiDOFJointTrajectoryPoint_H_ */
