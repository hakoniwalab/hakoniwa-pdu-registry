#ifndef _pdu_ctype_sensor_msgs_MagneticField_H_
#define _pdu_ctype_sensor_msgs_MagneticField_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Vector3 magnetic_field;
        Hako_float64 magnetic_field_covariance[9];
} Hako_MagneticField;

#endif /* _pdu_ctype_sensor_msgs_MagneticField_H_ */
