#ifndef _pdu_ctype_geometry_msgs_AccelWithCovariance_H_
#define _pdu_ctype_geometry_msgs_AccelWithCovariance_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Accel.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        Hako_Accel accel;
        Hako_float64 covariance[36];
} Hako_AccelWithCovariance;

#endif /* _pdu_ctype_geometry_msgs_AccelWithCovariance_H_ */
