#ifndef _pdu_ctype_geometry_msgs_PoseArray_H_
#define _pdu_ctype_geometry_msgs_PoseArray_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        // Pose poses[]
        int _poses_len;
        int _poses_off;
} Hako_PoseArray;

#endif /* _pdu_ctype_geometry_msgs_PoseArray_H_ */
