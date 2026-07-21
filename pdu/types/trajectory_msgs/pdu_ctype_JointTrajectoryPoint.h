#ifndef _pdu_ctype_trajectory_msgs_JointTrajectoryPoint_H_
#define _pdu_ctype_trajectory_msgs_JointTrajectoryPoint_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Duration.h"

typedef struct {
        // float64 positions[]
        int _positions_len;
        int _positions_off;
        // float64 velocities[]
        int _velocities_len;
        int _velocities_off;
        // float64 accelerations[]
        int _accelerations_len;
        int _accelerations_off;
        // float64 effort[]
        int _effort_len;
        int _effort_off;
        Hako_Duration time_from_start;
} Hako_JointTrajectoryPoint;

#endif /* _pdu_ctype_trajectory_msgs_JointTrajectoryPoint_H_ */
