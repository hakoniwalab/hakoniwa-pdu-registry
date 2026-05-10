#ifndef _pdu_ctype_sensor_msgs_NavSatFix_H_
#define _pdu_ctype_sensor_msgs_NavSatFix_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "sensor_msgs/pdu_ctype_NavSatStatus.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_NavSatStatus status;
        Hako_float64 latitude;
        Hako_float64 longitude;
        Hako_float64 altitude;
        Hako_float64 position_covariance[9];
        Hako_uint8 position_covariance_type;
} Hako_NavSatFix;

#endif /* _pdu_ctype_sensor_msgs_NavSatFix_H_ */
