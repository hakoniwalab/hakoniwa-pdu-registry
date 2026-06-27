#ifndef _pdu_ctype_sensor_msgs_Range_H_
#define _pdu_ctype_sensor_msgs_Range_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_uint8 radiation_type;
        Hako_float32 field_of_view;
        Hako_float32 min_range;
        Hako_float32 max_range;
        Hako_float32 range;
        Hako_float32 variance;
} Hako_Range;

#endif /* _pdu_ctype_sensor_msgs_Range_H_ */
