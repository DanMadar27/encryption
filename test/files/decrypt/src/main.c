#include "../../../../lib/encryption.h"
#include "../../../../lib/math_operations.h"
#include "../../lib/files_operations.h"
#include "../../../../res/keys_domain.h"
#include "../../../../res/numbers.h"
#include "../../res/paths.h"
#include "../../res/random_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main ()
{
    clock_t start_decryption;
    clock_t end_decryption;

    double cpu_time_used_decryption;

    FILE *test_file;
    
    static char plaintext[PLAINTEXT_MAX] = {ZERO};
    static char ciphertext[CIPHERTEXT_MAX] = {ZERO};
    static char d[D_MAX];
    static char e[E_MAX];
    CommonKey *ck;

    int plaintext_length;


    printf("\n\n");
    printf("opening file : %s\n\n", FILENAME);

    // r mode is for reading

    test_file = fopen(FILE_PATH, "r");

    if (!test_file)
    {
        printf("error - could not open file\n\n");

        return EXIT_FAILURE;
    }


    fileToString(test_file, ciphertext, CIPHERTEXT_MAX);


    if (fclose(test_file))
    {
        printf("error when closing file\n\n");

        return EXIT_FAILURE;
    }


    ck = malloc (sizeof(CommonKey));
        
    if (!ck)
    {
        printf("error when allocating memory to ck\n");
        
        free(ck);

        return EXIT_FAILURE;
    }


    // Use shared seed with encrypt file for random generator 
    srand(SEED);


    start_decryption = clock();

    generateKeys (d, e, ck);

    printf("decrypting file : %s\n\n", FILENAME);

    plaintext_length = decrypt (ciphertext, plaintext, d, ck);

    end_decryption = clock();

    cpu_time_used_decryption = ((double) (end_decryption - start_decryption)) / CLOCKS_PER_SEC;


    // w mode is for writing

    test_file = fopen(FILE_PATH, "w");

    stringToFileLength (plaintext, test_file, plaintext_length);


    if (fclose(test_file))
    {
        printf("error when closing file\n\n");

        free(ck);

        return EXIT_FAILURE;
    }


    printf ("decryption took %f seconds\n\n", cpu_time_used_decryption);

    free(ck);

    return EXIT_SUCCESS;
}