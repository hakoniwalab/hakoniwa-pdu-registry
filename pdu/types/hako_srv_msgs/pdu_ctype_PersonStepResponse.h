#ifndef _pdu_ctype_hako_srv_msgs_PersonStepResponse_H_
#define _pdu_ctype_hako_srv_msgs_PersonStepResponse_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "geometry_msgs/pdu_ctype_Transform.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "sensor_msgs/pdu_ctype_JointState.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_uint64 step;
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        Hako_Transform pose;
        Hako_Twist twist;
        Hako_JointState joints;
} Hako_PersonStepResponse;

#endif /* _pdu_ctype_hako_srv_msgs_PersonStepResponse_H_ */
