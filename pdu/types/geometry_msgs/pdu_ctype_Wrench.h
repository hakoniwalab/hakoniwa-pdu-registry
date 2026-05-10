#ifndef _pdu_ctype_geometry_msgs_Wrench_H_
#define _pdu_ctype_geometry_msgs_Wrench_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        Hako_Vector3 force;
        Hako_Vector3 torque;
} Hako_Wrench;

#endif /* _pdu_ctype_geometry_msgs_Wrench_H_ */
