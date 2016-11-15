
#ifndef __XMR_CRYPTONOTE_BASIC_H__
#define __XMR_CRYPTONOTE_BASIC_H__

#include "crypto.h";

typedef

typedef struct xmr_address_t
{
  xmr_public_key spend_key;
  xmr_public_key view_key;
} xmr_address;

bool xmr_get_account_address_as_str(bool integrated, bool testnet, const xmr_address *address, const xmr_hash *payment_id, char *encoded_addr);

#endif
