#include "../../../lib/test_encryption.h"
#include "../../../lib/math_operations.h"
#include "../../../lib/input_operations.h"
#include "../../../res/keys_domain.h"
#include "../../../res/numbers.h"
#include "../res/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main ()
{
    char user_action[USER_ACTION_MAX] = {ZERO};
    char is_pause;


    double cpu_time_used_total;


    static char d[D_MAX];
    static char e[E_MAX];
    CommonKey *ck;


    static char test_plaintexts[TOTAL_TESTS][PLAINTEXT_MAX] = {0};
    char *plaintext;
    int plaintext_length;
    int plaintext_min;
    int plaintext_max;
    
    int i;


    cpu_time_used_total = ZERO;


    // Use current time as seed for random generator 
    srand(time(0)); 


    plaintext_min = ONE;
    
    plaintext_max = PLAINTEXT_SIZE;

    plaintext = *test_plaintexts;

    for (i = ZERO; i < TOTAL_TESTS; ++i, plaintext += PLAINTEXT_MAX)
    {
        plaintext_length = (rand() %  
            (plaintext_max - plaintext_min + ONE)) + plaintext_min;


        randStr (plaintext, plaintext_length, MIN__CHAR, MAX__CHAR);
    }

    ck = malloc (sizeof(CommonKey));
    
    if (!ck)
    {
        printf("error when allocating memory to ck\n");
        
        free(ck);

        return EXIT_FAILURE;
    }

    cpu_time_used_total += testGenerateKeys (d, e, ck);


    is_pause = ONE;

    plaintext = *test_plaintexts;

    for (i = ZERO; i < TOTAL_TESTS; ++i, plaintext += PLAINTEXT_MAX)
    {
        if (is_pause)
        {
            printf(INPUT_MESSAGE);


            if (!fgets(user_action, USER_ACTION_MAX, stdin))
            {
                printf("Error when getting input from user\n\n");

                free(ck);

                return EXIT_FAILURE;
            }

            clear (user_action);            

            is_pause = strcmp(user_action, NO_PAUSE_ACTION);
        }


        cpu_time_used_total += testEncryptDecrypt (plaintext, d, e, ck);
    }


    printf ("total time  :  %f seconds\n\n", cpu_time_used_total);

    free(ck);

    return EXIT_SUCCESS;
}