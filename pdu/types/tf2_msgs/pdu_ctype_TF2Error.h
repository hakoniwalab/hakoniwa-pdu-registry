#ifndef _pdu_ctype_tf2_msgs_TF2Error_H_
#define _pdu_ctype_tf2_msgs_TF2Error_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint8 error;
        char error_string[HAKO_STRING_SIZE];
} Hako_TF2Error;

#endif /* _pdu_ctype_tf2_msgs_TF2Error_H_ */
