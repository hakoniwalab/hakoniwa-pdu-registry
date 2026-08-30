#ifndef _pdu_cpptype_ackermann_msgs_AckermannDriveStamped_HPP_
#define _pdu_cpptype_ackermann_msgs_AckermannDriveStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "ackermann_msgs/pdu_cpptype_AckermannDrive.hpp"
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_AckermannDrive drive;
} HakoCpp_AckermannDriveStamped;

#endif /* _pdu_cpptype_ackermann_msgs_AckermannDriveStamped_HPP_ */
