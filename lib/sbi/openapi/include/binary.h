#ifndef OGS_SBI_BINARY_H
#define OGS_SBI_BINARY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_binary_s {
    uint8_t* data;
    unsigned int len;
} ogs_sbi_binary_t;

ogs_sbi_binary_t *ogs_sbi_instantiate_binary_t(char *data, int len);

char *ogs_sbi_base64encode(const void *b64_encode_this,
                           int encode_this_many_bytes);

char *ogs_sbi_base64decode(const void *b64_decode_this,
                           int decode_this_many_bytes, int *decoded_bytes);

#ifdef __cplusplus
}
#endif

#endif // OGS_SBI_BINARY_H
