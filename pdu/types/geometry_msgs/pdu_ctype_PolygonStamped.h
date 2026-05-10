#ifndef _pdu_ctype_geometry_msgs_PolygonStamped_H_
#define _pdu_ctype_geometry_msgs_PolygonStamped_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point32.h"
#include "geometry_msgs/pdu_ctype_Polygon.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_Polygon polygon;
} Hako_PolygonStamped;

#endif /* _pdu_ctype_geometry_msgs_PolygonStamped_H_ */
