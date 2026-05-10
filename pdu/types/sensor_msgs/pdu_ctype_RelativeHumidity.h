#ifndef _pdu_ctype_sensor_msgs_RelativeHumidity_H_
#define _pdu_ctype_sensor_msgs_RelativeHumidity_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_float64 relative_humidity;
        Hako_float64 variance;
} Hako_RelativeHumidity;

#endif /* _pdu_ctype_sensor_msgs_RelativeHumidity_H_ */
