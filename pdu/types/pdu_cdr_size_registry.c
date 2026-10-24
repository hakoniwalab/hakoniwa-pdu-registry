#include "pdu_cdr_size_registry.h"
#include <string.h>

static const HakoPduCdrSizeEntry g_pdu_cdr_size_table[] = {
    { "builtin_interfaces/Time", 12 },
    { "geometry_msgs/Point", 28 },
    { "geometry_msgs/Pose", 60 },
    { "geometry_msgs/Quaternion", 36 },
    { "hako_msgs/ContactEvent", 69 },
    { "hako_msgs/ContactEventArray", 8 },
    { "hako_srv_msgs/RenderCameraFrameRequest", 84 },
    { "hako_srv_msgs/RenderCameraFrameRequestPacket", 108 },
    { "hako_srv_msgs/RenderCameraFrameResponse", 140 },
    { "hako_srv_msgs/RenderCameraFrameResponsePacket", 164 },
    { "hako_srv_msgs/RenderCameraRequest", 76 },
    { "hako_srv_msgs/RenderCameraRequestPacket", 100 },
    { "hako_srv_msgs/RenderCameraResponse", 60 },
    { "hako_srv_msgs/RenderCameraResponsePacket", 84 },
    { "hako_srv_msgs/RenderObject", 76 },
    { "hako_srv_msgs/ServiceRequestHeader", 28 },
    { "hako_srv_msgs/ServiceResponseHeader", 28 },
    { "sensor_msgs/Image", 44 },
    { "std_msgs/Header", 17 },
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
