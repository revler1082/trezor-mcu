
#include <string.h>
#include <stdlib.h>

#include "base58.h"
#include "constants.h"
#include "cryptonote-basic.h"
#include "../sha3.h"

void xmr_encode_varint(uint64_t value, uint8_t **ptr, size_t *incount)
{
	uint8_t *p = *ptr;
	size_t count = 1;
    while (value >= 0x80)
	{
        *p++ = ((uint8_t)(value & 0x7F)) | 0x80;
        value >>= 7;
        ++count;
    }

	*p++ = ((uint8_t)value) & 0x7F;
	*ptr += count;
	*incount += count;
}

bool xmr_get_account_address_as_str(bool integrated, bool testnet, const xmr_address *address, const xmr_hash *payment_id, char *encoded_addr)
{
	uint8_t buffer[256];
	size_t len = 0;

	uint8_t tag;

	if(integrated)
		tag = testnet ? XMR_TESTNET_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX : XMR_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX;
	else
		tag = testnet ? XMR_TESTNET_PUBLIC_ADDRESS_BASE58_PREFIX : XMR_PUBLIC_ADDRESS_BASE58_PREFIX;

	uint8_t *p = buffer;
	xmr_encode_varint(tag, &p, &len);

	memcpy(buffer + len, address->spend_key.data, sizeof(address->spend_key.data));
	len += sizeof(address->spend_key.data);
	memcpy(buffer + len, address->view_key.data, sizeof(address->view_key.data));
	len += sizeof(address->view_key.data);

	if(integrated)
	{
		memcpy(buffer + len, payment_id, XMR_ENCRYPTED_PAYMENT_ID_SIZE);
		len += XMR_ENCRYPTED_PAYMENT_ID_SIZE;
	}

	xmr_hash checksum;
	//keccak(buffer, len, checksum.data, sizeof(checksum.data));
	SHA3_CTX ctx;
  keccak_256_Init(&ctx);
  keccak_Update(&ctx, buffer, len);
  keccak_Final(&ctx, checksum.data);
	memcpy(buffer + len, checksum.data, XMR_ADDRESS_CHECKSUM_SIZE);
	len += XMR_ADDRESS_CHECKSUM_SIZE;
	xmr_b58_encode(buffer, len, encoded_addr);

	return true;
}
