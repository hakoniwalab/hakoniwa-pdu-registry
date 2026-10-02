#ifndef _pdu_ctype_hako_msgs_ContactEvent_H_
#define _pdu_ctype_hako_msgs_ContactEvent_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"

typedef struct {
        Hako_Time stamp;
        char self_name[HAKO_STRING_SIZE];
        char other_name[HAKO_STRING_SIZE];
        char other_kind[HAKO_STRING_SIZE];
        Hako_Point position;
        Hako_float64 relative_speed;
        Hako_bool started;
} Hako_ContactEvent;

#endif /* _pdu_ctype_hako_msgs_ContactEvent_H_ */
