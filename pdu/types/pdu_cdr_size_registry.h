#ifndef HAKO_PDU_CDR_SIZE_REGISTRY_H
#define HAKO_PDU_CDR_SIZE_REGISTRY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* type_name;
    uint32_t size;
} HakoPduCdrSizeEntry;

const HakoPduCdrSizeEntry* hako_pdu_cdr_size_table(void);
size_t hako_pdu_cdr_size_count(void);
int hako_pdu_cdr_get_size(const char* type_name, uint32_t* out_size);

#ifdef __cplusplus
}
#endif

#endif /* HAKO_PDU_CDR_SIZE_REGISTRY_H */
