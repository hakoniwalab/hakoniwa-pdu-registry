#ifndef _pdu_ctype_hako_msgs_ContactEventArray_H_
#define _pdu_ctype_hako_msgs_ContactEventArray_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "hako_msgs/pdu_ctype_ContactEvent.h"

typedef struct {
        // ContactEvent events[]
        int _events_len;
        int _events_off;
} Hako_ContactEventArray;

#endif /* _pdu_ctype_hako_msgs_ContactEventArray_H_ */
