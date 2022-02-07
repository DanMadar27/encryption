#include "../lib/encryption.h"
#include "../lib/math_operations.h"
#include "../lib/string_operations.h"
#include "../res/keys_domain.h"
#include "../res/numbers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void printKeys (char *d, char *e, CommonKey *ck)
{
    printf("keys are : \n\n");

    printf("d : %s\n\n\n", d);
    printf("e : %s\n\n\n", e);
    printf("n_mod : %s\n\n\n", ck->n_mod);
    printf("n_xor : %s\n\n\n", ck->n_xor);
    printf("n_shift1 : %s\n\n\n", ck->n_shift1);
    printf("n_shift2 : %s\n\n\n", ck->n_shift2);
    printf("\n\n");
}


void generateKeys (char *d, char *e, CommonKey *ck)
{
    if (!D_SIZE || !E_SIZE || !MOD_SIZE || !XOR_SIZE || !SHIFT_SIZE)
    {
        printf ("error - size of keys is 0\n\n");

        free (ck);
        
        exit (EXIT_FAILURE);
    }

    
    randStr (ck->n_mod, MOD_SIZE, ONE_CHAR, BASE_MINUS_ONE_CHAR);

    randStr (d, D_SIZE, ONE_CHAR, BASE_MINUS_ONE_CHAR);

    mult(ck->n_mod, MOD_DIV_D_E, e);
    sub (e, d, e);

    // if length of e is not E_SIZE then add 0 in start of e
    // (so it will be with length of E_SIZE)
    if (strlen (e) < E_SIZE)
    {
        shiftCharsRight(e, E_SIZE);
        *e = ZERO_CHAR;
    }

    randStr (ck->n_xor, XOR_SIZE, ONE_CHAR, BASE_MINUS_ONE_CHAR);
    
    randStr (ck->n_shift1, SHIFT_SIZE, ONE_CHAR, BASE_MINUS_ONE_CHAR);
    
    randStr (ck->n_shift2, SHIFT_SIZE, ONE_CHAR, BASE_MINUS_ONE_CHAR);    
}


void encrypt (char *plaintext, char *ciphertext, char *e, CommonKey *ck)
{
    if (!(*plaintext))
    {
        *ciphertext = ZERO;

        return;
    }


    stringToOctal (plaintext, ciphertext);

    add (ciphertext, e, ciphertext);

    modN (ciphertext, ck->n_mod, ciphertext);

    xor (ciphertext, ck->n_xor, ciphertext);

    circularShiftRightCharT (ciphertext, ck->n_shift2);

    circularShiftLeftCharT (ciphertext, ck->n_shift1);
}


void encryptLength (char *plaintext, int plaintext_length,
    char *ciphertext, char *e, CommonKey *ck)
{   
    if (!(*plaintext))
    {
        *ciphertext = ZERO;

        return;
    }


    stringToOctalLength (plaintext, ciphertext, plaintext_length);

    add (ciphertext, e, ciphertext);

    modN (ciphertext, ck->n_mod, ciphertext);

    xor (ciphertext, ck->n_xor, ciphertext);

    circularShiftRightCharT (ciphertext, ck->n_shift2);

    circularShiftLeftCharT (ciphertext, ck->n_shift1);
}


int decrypt (char *ciphertext, char *plaintext, char *d, CommonKey *ck)
{
    if (!(*ciphertext))
    {
        *plaintext = ZERO;
        
        return ZERO;
    }


    circularShiftRightCharT (ciphertext, ck->n_shift1);

    circularShiftLeftCharT (ciphertext, ck->n_shift2);

    xor (ciphertext, ck->n_xor, ciphertext);

    add (ciphertext, d, ciphertext);

    modN (ciphertext, ck->n_mod, ciphertext);

    return octalToString (ciphertext, plaintext);
}


char * membersToPublicKey (char *e, CommonKey *ck)
{
    char *public_key;


    public_key = malloc (sizeof(char) * PUBLIC_KEY_MAX);
    
    if (!public_key)
    {
        printf("error when allocating memory to public_key\n");
        
        free(public_key);

        return ZERO;
    }

    memset (public_key, ZERO, sizeof(char) * PUBLIC_KEY_MAX);

    strcat(public_key, e);

    strcat(public_key, ck->n_mod);

    strcat(public_key, ck->n_xor);

    strcat(public_key, ck->n_shift1);

    strcat(public_key, ck->n_shift2);


    return public_key;
}


char publicKeyToMembers (char *public_key, char *e, CommonKey *ck)
{
    char *public_key_ptr;


    public_key_ptr = public_key;

    strncpy (e, public_key_ptr, E_SIZE);

    public_key_ptr += E_SIZE;


    strncpy (ck->n_mod, public_key_ptr, MOD_SIZE);

    public_key_ptr += MOD_SIZE;


    strncpy (ck->n_xor, public_key_ptr, XOR_SIZE);

    public_key_ptr += XOR_SIZE;


    strncpy (ck->n_shift1, public_key_ptr, SHIFT_SIZE);

    public_key_ptr += SHIFT_SIZE;


    strncpy (ck->n_shift2, public_key_ptr, SHIFT_SIZE);

    public_key_ptr += SHIFT_SIZE;


    return EXIT_SUCCESS;
}