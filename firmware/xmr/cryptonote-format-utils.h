#ifndef __XMR_CRYONOTE_FORMAT_UTILS_H
#define __XMR_CRYONOTE_FORMAT_UTILS_H

#include <stddef.h>
#include "xmr/crypto.h"

bool xmr_encrypt_payment_id(const xmr_public_key *pubkey, const xmr_secret_key *seckey, uint8_t *payment_id);
void xmr_add_tx_pubkey_to_extra(const xmr_public_key *tx_pubkey, uint8_t *extra, size_t *count);
void xmr_add_payment_id_to_extra(const uint8_t *payment_id, size_t payment_id_size, const xmr_public_key *pubkey, const xmr_secret_key *seckey, uint8_t *extra, size_t *count);

#endif
