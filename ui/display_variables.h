#pragma once

#include "os.h"

// A path contains 10 elements max, which max length in ascii is 1 whitespace +
// 10 char + optional quote "'" + "/" + \0"
#define MAX_DERIV_PATH_ASCII_LENGTH 1 + 10 * (10 + 2) + 1
#define MAX_CHAR_PER_LINE 25

typedef struct swap_data_s {
  int was_address_checked;
  // total number of inputs to be signed
  int totalNumberOfInputs;
  // number of already signed input in the transaction, to compare with
  // totalNumberOfInputs and exit properly
  int alreadySignedInputs;
  int initialized;
  unsigned char amount[8];
  unsigned char fees[8];
  char destination_address[65];
} swap_data_t;

union display_variables {
  struct {
    // char addressSummary[40]; // beginning of the output address ... end
    // of

    char fullAddress[65]; // the address
    char fullAmount[28];  // full amount
    char feesAmount[28];  // fees
  } tmp;

  struct {
    char derivation_path[MAX_DERIV_PATH_ASCII_LENGTH];
  } tmp_warning;

  swap_data_t swap_data;
};

extern union display_variables vars;
