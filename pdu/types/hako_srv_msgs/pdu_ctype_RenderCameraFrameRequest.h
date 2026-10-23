#ifndef _pdu_ctype_hako_srv_msgs_RenderCameraFrameRequest_H_
#define _pdu_ctype_hako_srv_msgs_RenderCameraFrameRequest_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"

typedef struct {
        char camera_name[HAKO_STRING_SIZE];
        Hako_uint64 sim_time_usec;
        Hako_Pose camera_pose;
        Hako_uint8 outputs;
} Hako_RenderCameraFrameRequest;

#endif /* _pdu_ctype_hako_srv_msgs_RenderCameraFrameRequest_H_ */
