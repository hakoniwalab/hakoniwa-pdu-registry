#ifndef _pdu_ctype_sensor_msgs_Joy_H_
#define _pdu_ctype_sensor_msgs_Joy_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        // float32 axes[]
        int _axes_len;
        int _axes_off;
        // int32 buttons[]
        int _buttons_len;
        int _buttons_off;
} Hako_Joy;

#endif /* _pdu_ctype_sensor_msgs_Joy_H_ */
