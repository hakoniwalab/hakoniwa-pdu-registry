#ifndef _pdu_ctype_hako_srv_msgs_AttachRequest_H_
#define _pdu_ctype_hako_srv_msgs_AttachRequest_H_

#include "pdu_primitive_ctypes.h"

typedef struct {
        char asset_name[HAKO_STRING_SIZE];
        Hako_uint64 delta_asset_tick;
} Hako_AttachRequest;

#endif /* _pdu_ctype_hako_srv_msgs_AttachRequest_H_ */
