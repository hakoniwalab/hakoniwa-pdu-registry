#ifndef _pdu_ctype_geometry_msgs_WrenchStamped_H_
#define _pdu_ctype_geometry_msgs_WrenchStamped_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Vector3.h"
#include "geometry_msgs/pdu_ctype_Wrench.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Wrench wrench;
} Hako_WrenchStamped;

#endif /* _pdu_ctype_geometry_msgs_WrenchStamped_H_ */
