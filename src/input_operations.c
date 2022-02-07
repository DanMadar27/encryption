#include "../res/numbers.h"
#include <stdio.h>
#include <string.h>


void clear (char *str)
{
    char *str_ptr;

    // check if new line exist

    str_ptr = strchr(str, '\n');

    if(str_ptr)
    {
        *str_ptr = ZERO;
    } 

    else
    {
        // clear upto newline

        scanf("%*[^\n]");
        scanf("%*c");
    }

}