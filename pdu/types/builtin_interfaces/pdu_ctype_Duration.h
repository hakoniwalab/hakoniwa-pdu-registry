#ifndef _pdu_ctype_builtin_interfaces_Duration_H_
#define _pdu_ctype_builtin_interfaces_Duration_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_int32 sec;
        Hako_uint32 nanosec;
} Hako_Duration;

#endif /* _pdu_ctype_builtin_interfaces_Duration_H_ */
