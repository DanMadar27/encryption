#ifndef COMMON_KEY_H
#define COMMON_KEY_H

#include "../res/keys_domain.h"


typedef struct CommonKey
{
    char n_mod[MOD_MAX];
    char n_xor[XOR_MAX];
    char n_shift1[SHIFT_MAX];
    char n_shift2[SHIFT_MAX];  
} CommonKey;


#endif