#include "cryptonote-format-utils.h"
#include "constants.h"
#include "keccak.h"

bool xmr_encrypt_payment_id(uint8_t *payment_id, const xmr_public_key *pubkey, const xmr_secret_key *seckey)
{
	xmr_derivation derivation;
	xmr_hash hash;
	uint8_t data[sizeof(derivation.data) + 1];

	if (!xmr_generate_key_derivation(pubkey, seckey, &derivation))
		return false;

	memcpy(data, derivation.data, sizeof(derivation.data));
	data[sizeof(derivation.data)] = XMR_ENCRYPTED_PAYMENT_ID_TAIL;
	keccak(data, sizeof(data), hash.data, sizeof(hash.data));

	for (size_t i = 0; i < 8; i++)
		payment_id[i] ^= hash.data[i];

	return true;
}

void xmr_add_tx_pub_key_to_extra(const xmr_public_key *tx_pub_key, uint8_t *extra, size_t *count)
{
	extra[(*count)++] = TX_EXTRA_TAG_PUBKEY;
	memcpy(extra + *count, tx_pub_key->data, sizeof(tx_pub_key->data));
	*count += sizeof(tx_pub_key->data);
}

void xmr_add_payment_id_to_extra(const uint8_t *payment_id, size_t payment_id_size, const xmr_public_key *pubkey, const xmr_secret_key *seckey, uint8_t *extra, size_t *count)
{
  bool encrypted = payment_id_size == XMR_ENCRYPTED_PAYMENT_ID_SIZE;

	extra[(*count)++] = XMR_TX_EXTRA_NONCE;
	uint8_t sz = encrypted ? 0x09 : 0x21;
	extra[(*count)++] = sz;
	extra[(*count)++] = encrypted ? XMR_TX_EXTRA_NONCE_ENCRYPTED_PAYMENT_ID : XMR_TX_EXTRA_NONCE_PAYMENT_ID;
	if(encrypted)
	{
		uint8_t final[XMR_ENCRYPTED_PAYMENT_ID_SIZE];
		memcpy(final, payment_id, XMR_ENCRYPTED_PAYMENT_ID_SIZE);
		xmr_encrypt_payment_id(pubkey, seckey, final);
		for(size_t i = *count; i < *count + sz - 1; i++)
			extra[i] = final[i - *count];
	}
	else
	{
		for(size_t i = *count; i < *count + sz - 1; i++)
    extra[i] = payment_id[i - *count];
	}

  *count += sz - 1;
}
