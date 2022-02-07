#include "../lib/test_encryption.h"
#include "../lib/input_operations.h"
#include "../res/keys_domain.h"
#include "../res/numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main ()
{
    double cpu_time_used_total;

    static char plaintext[PLAINTEXT_MAX] = {ZERO};
    static char d[D_MAX];
    static char e[E_MAX];
    CommonKey *ck;


    ck = malloc (sizeof(CommonKey));
        
    if (!ck)
    {
        printf("error when allocating memory to ck\n");
        
        free(ck);

        return EXIT_FAILURE;
    }

    cpu_time_used_total = ZERO;


    // Use current time as seed for random generator 
    srand(time(0)); 


    cpu_time_used_total += testGenerateKeys (d, e, ck);



    printf("enter plaintext (maximum length is %d):  ", PLAINTEXT_SIZE);

    if (!fgets(plaintext, PLAINTEXT_MAX, stdin))
    {
        printf("Error when getting input from user\n\n");

        free(ck);
        
        return EXIT_FAILURE;
    }

    while (!(*plaintext) || *plaintext == '\n')
    {
        clear (plaintext); 


        printf("Error - you did not entered input, please enter plaintext"
        "(maximum length is %d):  ", PLAINTEXT_SIZE);


        if (!fgets(plaintext, PLAINTEXT_MAX, stdin))
        {
            printf("Error when getting input from user\n\n");

            free(ck);
            
            return EXIT_FAILURE;
        }   
    }



    cpu_time_used_total += testEncryptDecrypt (plaintext, d, e, ck);

    printf ("total time  :  %f seconds\n\n", cpu_time_used_total);



    free(ck);
    
    return EXIT_SUCCESS;
}