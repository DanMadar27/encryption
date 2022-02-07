#include "../lib/string_operations.h"
#include "../res/numbers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void reverse (char *str)
{
    char *start;
    char *end;
    char temp;

    

    for (end = str; *end; ++end);
    
    --end;


    for (start = str; start < end; ++start, --end)
    {
        temp = *start;

        *start = *end;

        *end = temp;
    }
}


void copyReverse (char *src, char *dst)
{
    char *src_end;
    char *dst_start;
    


    src_end = strEnd(src);

    --src_end;


    dst_start = dst;


    for (; src_end >= src; --src_end, ++dst_start)
    {
        *dst_start = *src_end;
    }


    *dst_start = ZERO;
}


void stringToOctal (char *src, char *dst)
{
    char *src_ptr;
    char *dst_ptr;


    dst_ptr = dst;


    for (src_ptr = src; *src_ptr; ++src_ptr)
    {
        *(dst_ptr++) = ((*src_ptr & SEVENTH_TO_EIGHTH_BITS) >> SIX) + ZERO_CHAR;

        *(dst_ptr++) = ((*src_ptr & FOURTH_TO_SIXTH_BITS) >> THREE) + ZERO_CHAR;

        *(dst_ptr++) = (*src_ptr & FIRST_TO_THIRD_BITS) + ZERO_CHAR;
    }


    *dst_ptr = ZERO;
}


void stringToOctalLength (char *src, char *dst, int src_length)
{
    char *src_ptr;
    char *dst_ptr;


    src_ptr = src;
    dst_ptr = dst;


    for (; src_length; --src_length, ++src_ptr)
    {
        *(dst_ptr++) = ((*src_ptr & SEVENTH_TO_EIGHTH_BITS) >> SIX) + ZERO_CHAR;

        *(dst_ptr++) = ((*src_ptr & FOURTH_TO_SIXTH_BITS) >> THREE) + ZERO_CHAR;

        *(dst_ptr++) = (*src_ptr & FIRST_TO_THIRD_BITS) + ZERO_CHAR;
    }


    *dst_ptr = ZERO;
}


int octalToString (char *src, char *dst)
{
    char *temp_str;
    char *temp_str_ptr;
    char *dst_ptr;
    int src_length;
    int temp_str_length;
    int dst_length;


    src_length = strlen(src);

    // adding 1 to length of temp_str to store 0 value in end
    // adding 2 in case of adding 0 chars in start of string  
    temp_str_length = src_length + THREE;


    temp_str = malloc (sizeof(char) * temp_str_length);
    
    if (!temp_str)
    {
        printf("error when allocating memory to temp_str\n");
    
        *dst = ZERO;
    
        free(temp_str);

        return ZERO;
    }

    memset (temp_str, ZERO, sizeof(char) * temp_str_length);


    switch (src_length % THREE)
    {

    case ONE:

        *temp_str = ZERO_CHAR;
        
        *(temp_str + ONE) = ZERO_CHAR;
    
        *(temp_str + TWO) = ZERO;

        break;


    case TWO:

        *temp_str = ZERO_CHAR;
        
        *(temp_str + ONE) = ZERO;

        break;

    }

    strcat(temp_str, src);


    temp_str_ptr = ignoreLeftZeroes(temp_str, THREE);
    dst_ptr = dst;

    
    dst_length = ZERO;

    while (*temp_str_ptr)
    {
        *dst_ptr = *(temp_str_ptr++) - ZERO_CHAR;

        *dst_ptr <<= THREE;

        *dst_ptr += *(temp_str_ptr++) - ZERO_CHAR;

        *dst_ptr <<= THREE;

        *dst_ptr += *(temp_str_ptr++) - ZERO_CHAR;


        ++dst_ptr;

        ++dst_length;
    }


    *dst_ptr = ZERO;

    return dst_length;
}


char * strEnd (char *str)
{
    char *str_end;

    for (str_end = str; *str_end; ++str_end);

    return str_end;
}


char * ignoreLeftZeroes(char *str, int jump)
{
    char *str_ptr;


    for (str_ptr = str; *str_ptr && isZeroCharSequence(str_ptr, str_ptr + jump);
        str_ptr += jump);


    return str_ptr;
}


char isZeroCharSequence (char *n, char *n_end)
{
    char *n_ptr;


    for (n_ptr = n; n_ptr < n_end; n_ptr++)
    {
        if (*n_ptr - ZERO_CHAR)
        {
            return ZERO;
        }
    }


    return ONE;
}


void shiftCharsRight (char *str, int len)
{
    int i;

    for(i = ZERO; i < len; ++i)
    {
        *(str + len - i) = *(str + len - i - 1);
    } 
}