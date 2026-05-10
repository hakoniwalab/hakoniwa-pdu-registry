#ifndef _pdu_ctype_sensor_msgs_NavSatStatus_H_
#define _pdu_ctype_sensor_msgs_NavSatStatus_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_int8 status;
        Hako_uint16 service;
} Hako_NavSatStatus;

#endif /* _pdu_ctype_sensor_msgs_NavSatStatus_H_ */
