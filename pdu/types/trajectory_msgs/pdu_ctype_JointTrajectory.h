#ifndef _pdu_ctype_trajectory_msgs_JointTrajectory_H_
#define _pdu_ctype_trajectory_msgs_JointTrajectory_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Duration.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"
#include "trajectory_msgs/pdu_ctype_JointTrajectoryPoint.h"

typedef struct {
        Hako_Header header;
        // string joint_names[]
        int _joint_names_len;
        int _joint_names_off;
        // JointTrajectoryPoint points[]
        int _points_len;
        int _points_off;
} Hako_JointTrajectory;

#endif /* _pdu_ctype_trajectory_msgs_JointTrajectory_H_ */
