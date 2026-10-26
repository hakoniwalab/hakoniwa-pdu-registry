#ifndef _pdu_ctype_hako_srv_msgs_AckermannStepRequest_H_
#define _pdu_ctype_hako_srv_msgs_AckermannStepRequest_H_

#include "pdu_primitive_ctypes.h"
#include "ackermann_msgs/pdu_ctype_AckermannDrive.h"

typedef struct {
        Hako_uint64 step;
        Hako_AckermannDrive drive;
} Hako_AckermannStepRequest;

#endif /* _pdu_ctype_hako_srv_msgs_AckermannStepRequest_H_ */
