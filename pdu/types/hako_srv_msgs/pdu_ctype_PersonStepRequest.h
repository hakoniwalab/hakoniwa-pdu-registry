#ifndef _pdu_ctype_hako_srv_msgs_PersonStepRequest_H_
#define _pdu_ctype_hako_srv_msgs_PersonStepRequest_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        Hako_uint64 step;
        Hako_Twist cmd_vel;
        char animation[HAKO_STRING_SIZE];
        char ride[HAKO_STRING_SIZE];
} Hako_PersonStepRequest;

#endif /* _pdu_ctype_hako_srv_msgs_PersonStepRequest_H_ */
