#include "pdu_cdr_size_registry.h"
#include <string.h>

static const HakoPduCdrSizeEntry g_pdu_cdr_size_table[] = {
    { "hako_srv_msgs/AttachRequest", 20 },
    { "hako_srv_msgs/AttachRequestPacket", 44 },
    { "hako_srv_msgs/AttachResponse", 44 },
    { "hako_srv_msgs/AttachResponsePacket", 68 },
    { "hako_srv_msgs/DetachRequest", 12 },
    { "hako_srv_msgs/DetachRequestPacket", 36 },
    { "hako_srv_msgs/DetachResponse", 8 },
    { "hako_srv_msgs/DetachResponsePacket", 32 },
    { "hako_srv_msgs/GetWorldTimeRequest", 12 },
    { "hako_srv_msgs/GetWorldTimeRequestPacket", 36 },
    { "hako_srv_msgs/GetWorldTimeResponse", 28 },
    { "hako_srv_msgs/GetWorldTimeResponsePacket", 52 },
    { "hako_srv_msgs/LogicalTime", 20 },
    { "hako_srv_msgs/NotifyAssetTimeRequest", 28 },
    { "hako_srv_msgs/NotifyAssetTimeRequestPacket", 52 },
    { "hako_srv_msgs/NotifyAssetTimeResponse", 8 },
    { "hako_srv_msgs/NotifyAssetTimeResponsePacket", 32 },
    { "hako_srv_msgs/ServiceRequestHeader", 28 },
    { "hako_srv_msgs/ServiceResponseHeader", 28 },
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
