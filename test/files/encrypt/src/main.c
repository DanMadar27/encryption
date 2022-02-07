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
    clock_t start_encryption;
    clock_t end_encryption;

    double cpu_time_used_encryption;

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


    plaintext_length = fileToString(test_file, plaintext, PLAINTEXT_MAX);


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


    // Use shared seed with decrypt file for random generator 
    srand(SEED);


    start_encryption = clock();

    generateKeys (d, e, ck);

    printf("encrypting file : %s\n\n", FILENAME);
    
    encryptLength (plaintext, plaintext_length, ciphertext, e, ck);
    
    end_encryption = clock();

    cpu_time_used_encryption = ((double) (end_encryption - start_encryption)) / CLOCKS_PER_SEC;


    // w mode is for writing

    test_file = fopen(FILE_PATH, "w");

    stringToFile(ciphertext, test_file);


    if (fclose(test_file))
    {
        printf("error when closing file\n\n");

        free(ck);

        return EXIT_FAILURE;
    }


    printf ("encryption took %f seconds\n\n", cpu_time_used_encryption);

    free(ck);

    return EXIT_SUCCESS;
}