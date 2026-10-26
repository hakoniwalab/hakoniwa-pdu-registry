#ifndef _pdu_ctype_hako_srv_msgs_AckermannStepResponse_H_
#define _pdu_ctype_hako_srv_msgs_AckermannStepResponse_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"

typedef struct {
        Hako_uint64 step;
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        Hako_Transform pose;
        Hako_Twist twist;
} Hako_AckermannStepResponse;

#endif /* _pdu_ctype_hako_srv_msgs_AckermannStepResponse_H_ */
