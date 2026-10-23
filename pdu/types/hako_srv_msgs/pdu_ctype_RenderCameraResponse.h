#ifndef _pdu_ctype_hako_srv_msgs_RenderCameraResponse_H_
#define _pdu_ctype_hako_srv_msgs_RenderCameraResponse_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "sensor_msgs/pdu_ctype_Image.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_uint32 result_code;
        Hako_uint64 sim_time_usec;
        Hako_Image image;
} Hako_RenderCameraResponse;

#endif /* _pdu_ctype_hako_srv_msgs_RenderCameraResponse_H_ */
