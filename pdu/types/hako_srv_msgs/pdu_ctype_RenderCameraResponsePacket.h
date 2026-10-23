#ifndef _pdu_ctype_hako_srv_msgs_RenderCameraResponsePacket_H_
#define _pdu_ctype_hako_srv_msgs_RenderCameraResponsePacket_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "hako_srv_msgs/pdu_ctype_RenderCameraResponse.h"
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"
#include "sensor_msgs/pdu_ctype_Image.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_ServiceResponseHeader header;
        Hako_RenderCameraResponse body;
} Hako_RenderCameraResponsePacket;

#endif /* _pdu_ctype_hako_srv_msgs_RenderCameraResponsePacket_H_ */
