#ifndef _pdu_ctype_geometry_msgs_TwistStamped_H_
#define _pdu_ctype_geometry_msgs_TwistStamped_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Twist.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Twist twist;
} Hako_TwistStamped;

#endif /* _pdu_ctype_geometry_msgs_TwistStamped_H_ */
