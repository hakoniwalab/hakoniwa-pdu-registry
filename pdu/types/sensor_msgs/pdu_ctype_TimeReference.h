#ifndef _pdu_ctype_sensor_msgs_TimeReference_H_
#define _pdu_ctype_sensor_msgs_TimeReference_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Time time_ref;
        char source[HAKO_STRING_SIZE];
} Hako_TimeReference;

#endif /* _pdu_ctype_sensor_msgs_TimeReference_H_ */
