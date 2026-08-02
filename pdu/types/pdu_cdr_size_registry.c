#include "pdu_cdr_size_registry.h"
#include <string.h>

static const HakoPduCdrSizeEntry g_pdu_cdr_size_table[] = {
    { "hako_action_msgs/ActionFeedbackHeader", 28 },
    { "hako_action_msgs/ActionRequestHeader", 24 },
    { "hako_action_msgs/ActionResponseHeader", 24 },
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
