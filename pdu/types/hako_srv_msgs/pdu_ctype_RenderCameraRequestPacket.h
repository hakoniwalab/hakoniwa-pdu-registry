#ifndef _pdu_ctype_hako_srv_msgs_RenderCameraRequestPacket_H_
#define _pdu_ctype_hako_srv_msgs_RenderCameraRequestPacket_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "hako_srv_msgs/pdu_ctype_RenderCameraRequest.h"
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"

typedef struct {
        Hako_ServiceRequestHeader header;
        Hako_RenderCameraRequest body;
} Hako_RenderCameraRequestPacket;

#endif /* _pdu_ctype_hako_srv_msgs_RenderCameraRequestPacket_H_ */
