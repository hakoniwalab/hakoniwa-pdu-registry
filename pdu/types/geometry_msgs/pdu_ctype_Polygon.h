#ifndef _pdu_ctype_geometry_msgs_Polygon_H_
#define _pdu_ctype_geometry_msgs_Polygon_H_

#include "pdu_primitive_ctypes.h"
#include "geometry_msgs/pdu_ctype_Point32.h"

typedef struct {
        // Point32 points[]
        int _points_len;
        int _points_off;
} Hako_Polygon;

#endif /* _pdu_ctype_geometry_msgs_Polygon_H_ */
