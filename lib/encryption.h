#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "common_key.h"

// print given keys
void printKeys (char *d, char *e, CommonKey *ck);


// generate keys and store them in given strings
// e - used to encrypt
// d - used to decrypt
// n - used to encrypt and decrypt
void generateKeys (char *d, char *e, CommonKey *ck);


// encrypt given plaintext with given e and n
// and stores the ciphertext in "ciphertext" parameter
void encrypt (char *plaintext, char *ciphertext, char *e, CommonKey *ck);

// encrypt with given length of plaintext
void encryptLength (char *plaintext, int plaintext_length,
    char *ciphertext, char *e, CommonKey *ck);


// decrypt given ciphertext with given d and n
// and stores the plaintext in "plaintext" parameter.
// return length of plaintext
int decrypt (char *ciphertext, char *plaintext, char *d, CommonKey *ck);


// return a string contains all public key members 
char * membersToPublicKey (char *e, CommonKey *ck);


// store values of public key members and return 0 if SUCCESS
char publicKeyToMembers (char *public_key, char *e, CommonKey *ck);


#endif