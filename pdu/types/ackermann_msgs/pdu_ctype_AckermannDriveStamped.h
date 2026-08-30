#ifndef _pdu_ctype_ackermann_msgs_AckermannDriveStamped_H_
#define _pdu_ctype_ackermann_msgs_AckermannDriveStamped_H_

#include "pdu_primitive_ctypes.h"
#include "ackermann_msgs/pdu_ctype_AckermannDrive.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
        Hako_AckermannDrive drive;
} Hako_AckermannDriveStamped;

#endif /* _pdu_ctype_ackermann_msgs_AckermannDriveStamped_H_ */
