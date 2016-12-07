
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "base58.h"

uint64_t xmr_uint_8be_to_64(const uint8_t *data, size_t size)
{
	assert(1 <= size && size <= sizeof(uint64_t));

	uint64_t res = 0;
	switch (9 - size)
	{
	case 1:            res |= *data++;
	case 2: res <<= 8; res |= *data++;
	case 3: res <<= 8; res |= *data++;
	case 4: res <<= 8; res |= *data++;
	case 5: res <<= 8; res |= *data++;
	case 6: res <<= 8; res |= *data++;
	case 7: res <<= 8; res |= *data++;
	case 8: res <<= 8; res |= *data; break;
	default: assert(false);
	}

	return res;
}

void xmr_b58_encode_block(const uint8_t *block, size_t size, char *res)
{
	assert(1 <= size && size <= XMR_B58_FULL_BLOCK_SIZE);
	uint64_t num = xmr_uint_8be_to_64((uint8_t *) block, size);
	size_t i = xmr_b58_encoded_block_sizes[size] - 1;
	while (0 < num)
	{
		uint64_t remainder = num % XMR_B58_ALPHABET_SIZE;
		num /= XMR_B58_ALPHABET_SIZE;
		res[i] = xmr_b58_alphabet[remainder];
		--i;
	}
}

void xmr_b58_encode(const uint8_t *data, size_t datalen, char *encoded)
{
	size_t block_count = datalen / XMR_B58_FULL_BLOCK_SIZE;
	size_t last_block_size = datalen % XMR_B58_FULL_BLOCK_SIZE;
	size_t res_size = block_count * XMR_B58_ENCODED_FULL_BLOCK_SIZE + xmr_b58_encoded_block_sizes[last_block_size];

	memset(encoded, xmr_b58_alphabet[0], res_size);

	for (size_t i = 0; i < block_count; i++)
	{
		xmr_b58_encode_block(data + i * XMR_B58_FULL_BLOCK_SIZE, XMR_B58_FULL_BLOCK_SIZE, &encoded[i * XMR_B58_ENCODED_FULL_BLOCK_SIZE]);
	}

	if (0 < last_block_size)
	{
	   xmr_b58_encode_block(data +  block_count * XMR_B58_FULL_BLOCK_SIZE, last_block_size, &encoded[block_count * XMR_B58_ENCODED_FULL_BLOCK_SIZE]);
	}

	encoded[res_size] = '\0';
}
