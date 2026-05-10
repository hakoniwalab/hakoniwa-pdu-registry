#ifndef _pdu_ctype_nav_msgs_MapMetaData_H_
#define _pdu_ctype_nav_msgs_MapMetaData_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"

typedef struct {
        Hako_Time map_load_time;
        Hako_float32 resolution;
        Hako_uint32 width;
        Hako_uint32 height;
        Hako_Pose origin;
} Hako_MapMetaData;

#endif /* _pdu_ctype_nav_msgs_MapMetaData_H_ */
