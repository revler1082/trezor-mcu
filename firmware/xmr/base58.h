////////////////////////////////////////////////////////////////////////////////
// b58 address encoder taken (from cryptonote)


#ifndef __XMR_BASE58_H__
#define __XMR_BASE58_H__

#include <stdint.h>
#include <stddef.h>

#include "../base58.h"
#include <assert.h>

static const char xmr_b58_alphabet[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
static const size_t xmr_b58_encoded_block_sizes[] = {0, 2, 3, 5, 6, 7, 9, 10, 11};

#define XMR_B58_ALPHABET_SIZE             58U
#define XMR_B58_FULL_BLOCK_SIZE           8U
#define XMR_B58_ENCODED_FULL_BLOCK_SIZE 	11U

uint64_t xmr_uint_8be_to_64(const uint8_t *data, size_t size);
void xmr_b58_encode_block(const uint8_t *block, size_t size, char *res);
void xmr_b58_encode(const uint8_t *data, size_t datalen, char *encoded);

#endif
