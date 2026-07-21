#include "pdu_cdr_size_registry.h"
#include <string.h>

static const HakoPduCdrSizeEntry g_pdu_cdr_size_table[] = {
    { "builtin_interfaces/Duration", 12 },
    { "builtin_interfaces/Time", 12 },
    { "geometry_msgs/Quaternion", 36 },
    { "geometry_msgs/Transform", 60 },
    { "geometry_msgs/Twist", 52 },
    { "geometry_msgs/Vector3", 28 },
    { "std_msgs/Header", 17 },
    { "trajectory_msgs/JointTrajectory", 28 },
    { "trajectory_msgs/JointTrajectoryPoint", 28 },
    { "trajectory_msgs/MultiDOFJointTrajectory", 28 },
    { "trajectory_msgs/MultiDOFJointTrajectoryPoint", 24 },
};

const HakoPduCdrSizeEntry* hako_pdu_cdr_size_table(void) {
    return g_pdu_cdr_size_table;
}

size_t hako_pdu_cdr_size_count(void) {
    return sizeof(g_pdu_cdr_size_table) / sizeof(g_pdu_cdr_size_table[0]);
}

int hako_pdu_cdr_get_size(const char* type_name, uint32_t* out_size) {
    if (type_name == NULL || out_size == NULL) {
        return -1;
    }
    size_t left = 0;
    size_t right = hako_pdu_cdr_size_count();
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        int cmp = strcmp(type_name, g_pdu_cdr_size_table[mid].type_name);
        if (cmp == 0) {
            *out_size = g_pdu_cdr_size_table[mid].size;
            return 0;
        }
        if (cmp < 0) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}
