#ifndef _pdu_ctype_nav_msgs_GridCells_H_
#define _pdu_ctype_nav_msgs_GridCells_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_float32 cell_width;
        Hako_float32 cell_height;
        // geometry_msgs/Point cells[]
        int _cells_len;
        int _cells_off;
} Hako_GridCells;

#endif /* _pdu_ctype_nav_msgs_GridCells_H_ */
