#ifndef _pdu_ctype_geometry_msgs_Inertia_H_
#define _pdu_ctype_geometry_msgs_Inertia_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        Hako_float64 m;
        Hako_Vector3 com;
        Hako_float64 ixx;
        Hako_float64 ixy;
        Hako_float64 ixz;
        Hako_float64 iyy;
        Hako_float64 iyz;
        Hako_float64 izz;
} Hako_Inertia;

#endif /* _pdu_ctype_geometry_msgs_Inertia_H_ */
