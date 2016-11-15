/*
 * This file is part of the TREZOR project.
 *
 * Copyright (C) 2016 Dion Ahmetaj <revler.1082@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __XMR_SIGNING_H__
#define __XMR_SIGNING_H__

#include <stdint.h>
#include <stdbool.h>
#include "bip32.h"
#include "messages.pb.h"

void xmr_signing_init(XmrSignTx *msg, const HDNode *node);
void xmr_signing_abort(void);
void xmr_signing_txack(XmrTxAck *msg);

#endif
