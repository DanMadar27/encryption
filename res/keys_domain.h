#ifndef KEYS_DOMAIN_H
#define KEYS_DOMAIN_H


// defining how many digits will be in keys (SIZE)
// and what is the limit of how many digits (MAX)
// in order to add null terminator in end of keys


#define PLAINTEXT_SIZE 100
#define PLAINTEXT_MAX (PLAINTEXT_SIZE + 1)


// define n_mod size = plaintext * 3 + 
// reason - n_mod > plaintext and
// each char in plaintext is 3 digits

#define MOD_SIZE (PLAINTEXT_SIZE * 3 + 1)
#define MOD_MAX (MOD_SIZE + 1)


// defining d - mod size - 1 and
// e - mod size + 1
// reason - e > n so n_mod in (e + plaintext) mod n_mod
// will always change the result

#define D_SIZE (MOD_SIZE - 1 )
#define D_MAX (D_SIZE + 1 )

#define E_SIZE (MOD_SIZE + 1 )
#define E_MAX (E_SIZE + 1 )


// define ciphertext SIZE maximum value of -
// E_SIZE + 2
// reason - (e + d + plaintext) - e is biggest
// and adding 2 for possible carries

#define CIPHERTEXT_SIZE (E_SIZE + 2)
#define CIPHERTEXT_MAX (CIPHERTEXT_SIZE + 1)


// define n_xor CIPHERTEXT_SIZE
// reason - change all bits in ciphertext

#define XOR_SIZE CIPHERTEXT_SIZE
#define XOR_MAX (XOR_SIZE + 1)


// define n_shift1, n_shift2 SIZE (large value)
// reason - change a lot of bits when encrypting

#define SHIFT_SIZE 3
#define SHIFT_MAX (SHIFT_SIZE + 1)


#define PUBLIC_KEY_SIZE (E_SIZE + MOD_SIZE + XOR_SIZE + SHIFT_SIZE + SHIFT_SIZE)
#define PUBLIC_KEY_MAX (PUBLIC_KEY_SIZE + 1)


// defining result of (e + d) / n_mod

#define MOD_DIV_D_E "2"


#endif