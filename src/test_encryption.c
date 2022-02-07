#include "../lib/encryption.h"
#include "../lib/math_operations.h"
#include "../res/keys_domain.h"
#include "../res/numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


double testGenerateKeys (char *d, char *e, CommonKey *ck)
{
    clock_t start_generate;
    clock_t end_generate;

    double cpu_time_used_generate;


    start_generate = clock();

    generateKeys (d, e, ck);


    end_generate = clock();

    cpu_time_used_generate = ((double) (end_generate - start_generate)) / CLOCKS_PER_SEC;


    printKeys (d, e, ck);


    printf ("generate keys took %f seconds\n\n", cpu_time_used_generate);


    return cpu_time_used_generate;
}


double testEncryptDecrypt (char *plaintext, char *d, char *e, CommonKey *ck)
{
    clock_t start_encrypt;
    clock_t start_decrypt;
    clock_t end_encrypt;
    clock_t end_decrypt;

    double cpu_time_used_encrypt;
    double cpu_time_used_decrypt;
    double cpu_time_used_total;

    static char ciphertext[CIPHERTEXT_MAX] = {ZERO};
    static char decrypt_result[PLAINTEXT_MAX] = {ZERO};


    printf("\n\n");

    printf("plaintext : %s\n\n", plaintext);


    start_encrypt = clock();

    encrypt(plaintext, ciphertext, e, ck);

    end_encrypt = clock();

    cpu_time_used_encrypt = ((double) (end_encrypt - start_encrypt)) / CLOCKS_PER_SEC;


    printf("ciphertext : %s\n\n", ciphertext);    


    start_decrypt = clock();

    decrypt(ciphertext, decrypt_result, d, ck);

    end_decrypt = clock();

    cpu_time_used_decrypt = ((double) (end_decrypt - start_decrypt)) / CLOCKS_PER_SEC;


    printf("decrypt result : %s\n\n", decrypt_result);

    if (strcmp(plaintext, decrypt_result))
    {
        printf("error - plaintext and decrypt result are not equal\n\n");

        free(ck);

        exit (EXIT_FAILURE);
    }

    else
    {
        printf("plaintext and decrypt result are equal\n\n");
    }
    
    
    printf("\n\n");


    cpu_time_used_total = cpu_time_used_encrypt +
        cpu_time_used_decrypt;

    printf ("encrypt took %f seconds\n\n", cpu_time_used_encrypt);
    printf ("decrypt took %f seconds\n\n", cpu_time_used_decrypt);
    printf ("total time of encrypt and decrypt :  %f seconds\n\n\n\n",
                cpu_time_used_total);


    return cpu_time_used_total;
}