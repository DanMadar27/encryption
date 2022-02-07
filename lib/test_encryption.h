#ifndef TEST_ENCRYPTION_H
#define TEST_ENCRYPTION_H

#include "common_key.h"


// generates keys and returns how much time it took
double testGenerateKeys (char *d, char *e, CommonKey *ck);


// reveive plaintext and performs encryption and
// decryption of it.
// returns how much time it took
double testEncryptDecrypt (char *plaintext, char *d, char *e, CommonKey *ck);


#endif