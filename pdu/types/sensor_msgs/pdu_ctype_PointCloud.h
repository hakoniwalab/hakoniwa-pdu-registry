#ifndef _pdu_ctype_sensor_msgs_PointCloud_H_
#define _pdu_ctype_sensor_msgs_PointCloud_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point32.h"
#include "sensor_msgs/pdu_ctype_ChannelFloat32.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        // geometry_msgs/Point32 points[]
        int _points_len;
        int _points_off;
        // ChannelFloat32 channels[]
        int _channels_len;
        int _channels_off;
} Hako_PointCloud;

#endif /* _pdu_ctype_sensor_msgs_PointCloud_H_ */
