#ifndef _pdu_ctype_hako_srv_msgs_RenderObject_H_
#define _pdu_ctype_hako_srv_msgs_RenderObject_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"

typedef struct {
        char name[HAKO_STRING_SIZE];
        char model[HAKO_STRING_SIZE];
        Hako_Pose pose;
} Hako_RenderObject;

#endif /* _pdu_ctype_hako_srv_msgs_RenderObject_H_ */
