#ifndef HAKO_PDU_SIZE_REGISTRY_H
#define HAKO_PDU_SIZE_REGISTRY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* type_name;
    uint32_t size;
} HakoPduSizeEntry;

const HakoPduSizeEntry* hako_pdu_size_table(void);
size_t hako_pdu_size_count(void);
int hako_pdu_get_size(const char* type_name, uint32_t* out_size);

#ifdef __cplusplus
}
#endif

#endif /* HAKO_PDU_SIZE_REGISTRY_H */
