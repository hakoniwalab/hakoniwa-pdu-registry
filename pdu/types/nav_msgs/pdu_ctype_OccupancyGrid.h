#ifndef _pdu_ctype_nav_msgs_OccupancyGrid_H_
#define _pdu_ctype_nav_msgs_OccupancyGrid_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "geometry_msgs/pdu_ctype_Point.h"
#include "geometry_msgs/pdu_ctype_Pose.h"
#include "geometry_msgs/pdu_ctype_Quaternion.h"
#include "nav_msgs/pdu_ctype_MapMetaData.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_MapMetaData info;
        // int8 data[]
        int _data_len;
        int _data_off;
} Hako_OccupancyGrid;

#endif /* _pdu_ctype_nav_msgs_OccupancyGrid_H_ */
