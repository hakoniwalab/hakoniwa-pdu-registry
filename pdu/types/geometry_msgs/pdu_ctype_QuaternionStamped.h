#ifndef _pdu_ctype_geometry_msgs_QuaternionStamped_H_
#define _pdu_ctype_geometry_msgs_QuaternionStamped_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Quaternion quaternion;
} Hako_QuaternionStamped;

#endif /* _pdu_ctype_geometry_msgs_QuaternionStamped_H_ */
