#ifndef _pdu_ctype_hako_srv_msgs_SetLightResponse_H_
#define _pdu_ctype_hako_srv_msgs_SetLightResponse_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        Hako_uint32 result_code;
        char message[HAKO_STRING_SIZE];
} Hako_SetLightResponse;

#endif /* _pdu_ctype_hako_srv_msgs_SetLightResponse_H_ */
