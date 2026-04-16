/*******************************************************************************
 *   Ledger App - Bitcoin Wallet
 *   (c) 2026 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include "io.h"

#include "apdu_constants.h"
#include "context.h"
#include "os_seed.h"

#define MASTER_KEY_FINGERPRINT_SIZE 4

/*
 * Function: handler_get_master_fingerprint
 * ----------------------------------------
 * Returns the 4-byte master key fingerprint (first 4 bytes of
 * RIPEMD160(SHA256(compressed_master_pubkey))).
 *
 * Uses the os_perso_get_master_key_identifier() OS syscall which
 * computes the BIP-32 key identifier internally, without requiring
 * the APPLICATION_FLAG_DERIVE_MASTER permission.
 *
 * Returns:
 *   - 4 bytes: master key fingerprint (big-endian)
 */
WEAK unsigned short handler_get_master_fingerprint(void) {
  uint8_t master_key_identifier[CX_RIPEMD160_SIZE] = {0};

  if (os_perso_get_master_key_identifier(master_key_identifier,
                                         CX_RIPEMD160_SIZE) != CX_OK) {
    return io_send_sw(SW_TECHNICAL_PROBLEM);
  }

  memmove(G_io_apdu_buffer, master_key_identifier, MASTER_KEY_FINGERPRINT_SIZE);
  context.outLength = MASTER_KEY_FINGERPRINT_SIZE;

  return io_send_response_pointer(G_io_apdu_buffer, MASTER_KEY_FINGERPRINT_SIZE,
                                  SW_OK);
}
