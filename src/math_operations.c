#include "../lib/math_operations.h"
#include "../lib/string_operations.h"
#include "../res/numbers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char isSmallerChar (char *a, char b)
{
    char *a_ptr;
    int a_length;


    a_ptr = ignoreLeftZeroes (a, ONE);


    a_length = strlen(a_ptr);
    

    if (a_length < ONE)
    {
        return ONE;
    }

    if (a_length > ONE)
    {
        return ZERO;
    }

    return *a_ptr < b;
}


char isSmaller (char *a, char *b)
{
    char *a_ptr;
    char *b_ptr;
    int a_length;
    int b_length;


    a_ptr = ignoreLeftZeroes (a, ONE);
    b_ptr = ignoreLeftZeroes (b, ONE);


    a_length = strlen(a_ptr);
    b_length = strlen(b_ptr);
    

    if (a_length < b_length)
    {
        return ONE;
    }

    if (a_length > b_length)
    {
        return ZERO;
    }


    for (; *a_ptr; ++a_ptr, ++b_ptr)
    {
        if (*a_ptr < *b_ptr)
        {
            return ONE;
        }

        if (*a_ptr > *b_ptr)
        {
            return ZERO;
        }
    }

    return ZERO;
}


char isGreater (char *a, char *b)
{
    char *a_ptr;
    char *b_ptr;
    int a_length;
    int b_length;


    a_ptr = ignoreLeftZeroes (a, ONE);
    b_ptr = ignoreLeftZeroes (b, ONE);


    a_length = strlen(a_ptr);
    b_length = strlen(b_ptr);
    
    
    if (a_length > b_length)
    {
        return ONE;
    }

    if (a_length < b_length)
    {
        return ZERO;
    }


    for (; a_ptr; ++a_ptr, ++b_ptr)
    {
        if (*a_ptr > *b_ptr)
        {
            return ONE;
        }

        if (*a_ptr < *b_ptr)
        {
            return ZERO;
        }
    }

    return ZERO;
}


char isZero (char *n)
{
    char *n_ptr;


    for (n_ptr = n; *n_ptr; n_ptr++)
    {
        if (*n_ptr - ZERO_CHAR)
        {
            return ZERO;
        }
    }


    return ONE;
}


void add (char *a, char *b, char *result)
{
    char *small_start;
    char *small_ptr;
    char *large_start;
    char *large_ptr;    
    char *reversed_result;
    char *reversed_result_ptr;
    int result_length;
    int a_length;
    int b_length;
    int sum;
    int carry;


    if (!(*a) || !(*b))
    {
        *result = ZERO;
        return;
    }


    a_length = strlen(a);
    b_length = strlen(b);

    if (a_length > b_length)
    {
        small_start = b;
        small_ptr = b + b_length - ONE;

        large_start = a;
        large_ptr = a + a_length - ONE;


        // adding 2 to result  length because there could be carry
        // and to set 0 value in last cell
        result_length = a_length + TWO;
    }

    else
    {
        small_start = a;
        small_ptr = a + a_length - ONE;

        large_start = b;
        large_ptr = b + b_length - ONE;


        // adding 2 to result length because there could be carry
        // and to set 0 value in last cell
        result_length = b_length + TWO;
    }


    reversed_result = malloc (sizeof(char) * result_length);
    
    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);
    
    reversed_result_ptr = reversed_result;


    carry = ZERO;


    for (; small_ptr >= small_start; --small_ptr,
        --large_ptr, ++reversed_result_ptr)
    {
        sum = (*small_ptr - ZERO_CHAR) +
            (*large_ptr - ZERO_CHAR) + carry;

        *reversed_result_ptr = (sum & BASE_MINUS_ONE) + ZERO_CHAR;

        carry = sum >> BASE_TOTAL_BITS;
    }


    for (; large_ptr >= large_start; --large_ptr, ++reversed_result_ptr)
    {
        sum = (*large_ptr - ZERO_CHAR) + carry;

        *reversed_result_ptr = (sum & BASE_MINUS_ONE) + ZERO_CHAR;

        carry = sum >> BASE_TOTAL_BITS;
    }

    if (carry)
    {
        *(reversed_result_ptr++) = carry + ZERO_CHAR;
    }


    copyReverse(reversed_result, result);


    free (reversed_result);
}


void addChar (char *a, char b, char *result)
{
    char *a_ptr;
    char *reversed_result;
    char *reversed_result_ptr;
    int result_length;
    int a_length;
    int sum;
    int carry;


    if (!(*a) || !b)
    {
        *result = ZERO;
        return;
    }


    a_length = strlen(a);
    
    a_ptr = a + a_length - ONE;
    
    // adding 2 to length because there could be carry
    // and to set 0 value in last cell
    result_length = a_length + TWO;

    reversed_result = malloc (sizeof(char) * result_length);
    
    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);
    
    reversed_result_ptr = reversed_result;


    sum = (*a_ptr - ZERO_CHAR) + (b - ZERO_CHAR);

    *(reversed_result_ptr++) = (sum & BASE_MINUS_ONE) + ZERO_CHAR;

    carry = sum >> BASE_TOTAL_BITS;

    --a_ptr;

    for (; a_ptr >= a; --a_ptr, ++reversed_result_ptr)
    {
        sum = (*a_ptr - ZERO_CHAR) + carry;

        *reversed_result_ptr = (sum & BASE_MINUS_ONE) + ZERO_CHAR;

        carry = sum >> BASE_TOTAL_BITS;
    }

    if (carry)
    {
        *(reversed_result_ptr++) = carry + ZERO_CHAR;
    }


    copyReverse(reversed_result, result);


    free (reversed_result);
}


void sub (char *a, char *b, char *result)
{
    char *a_ptr;
    char *b_ptr;
    char *reversed_result;
    char *reversed_result_ptr;
    int result_length;
    int sub;
    int carry;


    if (!(*a) || !(*b))
    {
        *result = ZERO;
        return;
    }


    if (isSmaller (a, b))
    {
        *result = ZERO;
        return;
    }


    // calcuating result length and most right digit in a and b
    a_ptr = strEnd(a);
    b_ptr = strEnd(b);


    result_length = a_ptr - a;

    // adding 1 to result length to store 0 value
    ++result_length;

    reversed_result = malloc (sizeof(char) * result_length);

    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);
    
    reversed_result_ptr = reversed_result;


    --a_ptr;
    --b_ptr;

    carry = ZERO;

    for (; b_ptr >= b; --b_ptr, --a_ptr, ++reversed_result_ptr)
    {
        sub = (*a_ptr - ZERO_CHAR) - (*b_ptr - ZERO_CHAR) - carry;

        if (sub < ZERO)
        {
            sub += BASE;
            carry = ONE;
        }

        else
        {
            carry = ZERO;
        }
        
        *reversed_result_ptr = sub + ZERO_CHAR;
    }

    for (; a_ptr >= a; --a_ptr, ++reversed_result_ptr)
    {
        sub = (*a_ptr - ZERO_CHAR) - carry;

        if (sub < ZERO)
        {
            sub += BASE;
            carry = ONE;
        }

        else
        {
            carry = ZERO;
        }
        
        *reversed_result_ptr = sub + ZERO_CHAR;
    }


    copyReverse(reversed_result, result);


    free (reversed_result);
}


void subChar (char *a, char b, char *result)
{
    char *a_ptr;
    char *reversed_result;
    char *reversed_result_ptr;
    int a_length;
    int result_length;
    int sub;
    int carry;


    if (!(*a) || !b)
    {
        *result = ZERO;
        return;
    }


    a_length = strlen(a);

    if (!a_length || (a_length == 1 && *a < b))
    {
        *result = ZERO;
        return;
    }


    // adding 1 to store 0 value 
    result_length = a_length + ONE;

    reversed_result = malloc (sizeof(char) * result_length);

    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);
    
    reversed_result_ptr = reversed_result;


    for (a_ptr = a; *a_ptr; ++a_ptr);

    --a_ptr;

    carry = ZERO;

    sub = (*a_ptr - ZERO_CHAR) - (b - ZERO_CHAR);

    if (sub < ZERO)
    {
        sub += BASE;
        carry = ONE;
    }

    *(reversed_result_ptr++) = sub + ZERO_CHAR;

    for (a_ptr -= ONE; a_ptr >= a; --a_ptr, ++reversed_result_ptr)
    {
        sub = (*a_ptr - ZERO_CHAR) - carry;

        if (sub < ZERO)
        {
            sub += BASE;
            carry = ONE;
        }

        else
        {
            carry = ZERO;
        }
        
        *reversed_result_ptr = sub + ZERO_CHAR;
    }


    copyReverse(reversed_result, result);


    free (reversed_result);
}


void mult (char *a, char *b, char *result)
{
    char *a_ptr;
    char *b_ptr;
    char *a_start;
    char *b_start;
    char *a_end;
    char *b_end;
    char *reversed_result;
    char *reversed_result_ptr;
    int result_length;
    int product;
    int carry;


    if (!(*a) || !(*b))
    {
        *result = ZERO;
        return;
    }


    if (isZero(a) || isZero(b))
    {
        *result = ZERO;
        return;
    }


    a_start = ignoreLeftZeroes(a, ONE);
    b_start = ignoreLeftZeroes(b, ONE);

    a_end = strEnd(a);
    b_end = strEnd(b);


    // adding 1 to result length to set 0 value in last cell
    result_length = (a_end - a_start) + (b_end - b_start) + ONE;

    reversed_result = malloc (sizeof(char) * result_length);
    
    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);

    

    reversed_result_ptr = reversed_result;

    for (a_ptr = a_end - ONE; a_ptr >= a_start; --a_ptr)
    {
        carry = ZERO;        


        reversed_result_ptr = reversed_result + (a_end - ONE -a_ptr);


        for (b_ptr = b_end- ONE; b_ptr >= b_start; --b_ptr, ++reversed_result_ptr)
        {
            *reversed_result_ptr = *reversed_result_ptr ?
                *reversed_result_ptr : ZERO_CHAR;


            product = (*a_ptr - ZERO_CHAR) * (*b_ptr - ZERO_CHAR) +
                (*reversed_result_ptr - ZERO_CHAR) + carry;

            
            *reversed_result_ptr = (product & BASE_MINUS_ONE) + ZERO_CHAR;

            carry = product >> BASE_TOTAL_BITS;
        }

        if (carry)
        {
            *reversed_result_ptr = *reversed_result_ptr ?
                *reversed_result_ptr : ZERO_CHAR;

            *reversed_result_ptr += carry;
        }
    }


    if (*result && isZero (result))
    {
        reverse(reversed_result);

        add (result, reversed_result, result);    
    }

    else
    {
        copyReverse(reversed_result, result);
    }


    free (reversed_result);
}


void divN (char *n, char *divisor, char *result)
{
    char *n_ptr;
    char *temp_result;
    char *temp_result_ptr;
    char *remainder;
    char *remainder_end;
    char quotient;
    int temp_result_length;
    int remainder_length;


    if (!(*n) || !(*divisor))
    {
        *result = ZERO;
        return;
    }


    if (isZero (divisor))
    {
        *result = ZERO;
        return;
    }


    remainder_length = strlen(n) + ONE;

    remainder = malloc (sizeof(char) * remainder_length);
    
    if (!remainder)
    {
        printf("error when allocating memory to remainder\n");

        *result = ZERO;

        free(remainder);

        return; 
    }

    memset (remainder, ZERO, sizeof(char) * remainder_length);
    
    remainder_end = remainder;


    temp_result_length = remainder_length;

    temp_result = malloc (sizeof(char) * temp_result_length);
    
    if (!temp_result)
    {
        printf("error when allocating memory to temp_result\n");

        *result = ZERO;
    
        free(temp_result);

        return; 
    }

    memset (temp_result, ZERO, sizeof(char) * temp_result_length);
    
    temp_result_ptr = temp_result;


    for (n_ptr = n; *n_ptr; ++n_ptr)
    {
        *remainder_end = *n_ptr;

        quotient = ZERO;

        for (; !isGreater (divisor, remainder);
            sub (remainder, divisor, remainder), ++quotient);

        
        *(temp_result_ptr++) = quotient + ZERO_CHAR;


        remainder_end = strEnd(remainder);
    }


    *temp_result_ptr = ZERO;


    strcpy (result, temp_result);


    free(temp_result);
    free(remainder);
}


void modN (char *n, char *m, char *result)
{
    char *n_ptr;
    char *remainder;
    char *remainder_end;
    int remainder_length;


    if (!(*n) || !(*m))
    {
        *result = ZERO;
        return;
    }


    if (isZero (m))
    {
        *result = ZERO;
        return;
    }


    remainder_length = strlen(n) + ONE;

    remainder = malloc (sizeof(char) * remainder_length);
    
    if (!remainder)
    {
        printf("error when allocating memory to remainder\n");

        *result = ZERO; 
    
        free(remainder);

        return;
    }

    memset (remainder, ZERO, sizeof(char) * remainder_length);
    
    remainder_end = remainder;


    for (n_ptr = n; *n_ptr; ++n_ptr)
    {
        *remainder_end = *n_ptr;

        for (; !isGreater (m, remainder);
            sub (remainder, m, remainder));

        remainder_end = strEnd(remainder);
    }

    strcpy(result, remainder);

    free(remainder);
}


void xor (char *a, char *b, char *result)
{
    char *a_ptr;
    char *b_ptr;
    char *temp_start;
    char *temp_ptr;
    char *reversed_result;
    char *reversed_result_ptr;
    int result_length;
    int a_length;
    int b_length;


    if (!(*a) || !(*b))
    {
        *result = ZERO;
        return;
    }


    a_length = strlen(a);
    b_length = strlen(b);
    
    a_ptr = a + a_length - ONE;
    b_ptr = b + b_length - ONE;


    if (a_length < b_length) 
    {
        temp_start = a;
        temp_ptr = a_ptr;

        result_length = b_length + ONE;
    }

    else
    {
        temp_start = b;
        temp_ptr = b_ptr;

        result_length = a_length + ONE;
    }
    

    reversed_result = malloc (sizeof(char) * result_length);
    
    if (!reversed_result)
    {
        printf("error when allocating memory to reversed_result\n");
    
        *result = ZERO;
    
        free(reversed_result);

        return;
    }

    memset (reversed_result, ZERO, sizeof(char) * result_length);
    
    reversed_result_ptr = reversed_result;


    for (; temp_ptr >= temp_start; --temp_ptr,
        --a_ptr, --b_ptr, ++reversed_result_ptr)
    {
        *reversed_result_ptr = ((*a_ptr - ZERO_CHAR) ^ (*b_ptr - ZERO_CHAR)) +
            ZERO_CHAR;
    }


    for (; a_ptr >= a; --a_ptr, ++reversed_result_ptr)
    {
        *reversed_result_ptr = *a_ptr;
    }

    for (; b_ptr >= b; --b_ptr, ++reversed_result_ptr)
    {
        *reversed_result_ptr = *b_ptr;
    }


    copyReverse(reversed_result, result);


    free(reversed_result);
}


void circularShiftLeft (char *n)
{
    char *n_end;
    char *n_ptr;
    char carry;
    char temp;


    if (!(*n))
    {
        return;
    }


    n_end = n + strlen(n);

    carry = ZERO;


    for (n_ptr = n_end - ONE; n_ptr >=n; --n_ptr)
    {
        temp = (*n_ptr - ZERO_CHAR) & FOUR;

        *n_ptr = ((*n_ptr - ZERO_CHAR) << ONE) + ZERO_CHAR;

        // making sure value won't extend BASE limit
        *n_ptr = (*n_ptr & BASE_MINUS_ONE) + ZERO_CHAR;

        if (carry)
        {
            *n_ptr = ((*n_ptr - ZERO_CHAR) | ONE) + ZERO_CHAR;
        }


        carry = temp;
    }


    if (carry)
    {
        n_ptr = n_end - ONE;

        *n_ptr = ((*n_ptr - ZERO_CHAR) | ONE) + ZERO_CHAR;
    }
}


void circularShiftRight (char *n)
{
    char *n_ptr;
    char carry;
    char temp;


    if (!(*n))
    {
        return;
    }


    carry = ZERO;


    for (n_ptr = n; *n_ptr; ++n_ptr)
    {
        temp = (*n_ptr - ZERO_CHAR) & ONE;

        *n_ptr = ((*n_ptr - ZERO_CHAR) >> ONE) + ZERO_CHAR;

        if (carry)
        {
            *n_ptr = ((*n_ptr - ZERO_CHAR) | FOUR) + ZERO_CHAR;
        }

        carry = temp;
    }


    if (carry)
    {
        n_ptr = n;

        *n_ptr = ((*n_ptr - ZERO_CHAR) | FOUR) + ZERO_CHAR;
    }
}


void circularShiftLeftCharT (char *n, char *t)
{
    char *temp;
    int temp_length;


    if (!(*n))
    {
        return;
    }


    temp_length = strlen(t) + ONE;

    temp = malloc (sizeof(char) * temp_length);
    
    if (!temp)
    {
        printf("error when allocating memory to temp\n");
    
        *n = ZERO;
    
        free(temp);

        return;
    }

    memset (temp, ZERO, sizeof(char) * temp_length);
    
    strcpy(temp, t);


    for (; !isZero(temp); subChar(temp, ONE_CHAR, temp))
    {
        circularShiftLeft(n);
    }


    free(temp);
}


void circularShiftLeftIntT (char *n, int t)
{
    if (!(*n))
    {
        return;
    }


    for (; t; --t)
    {
        circularShiftLeft(n);
    }
}


void circularShiftRightCharT (char *n, char *t)
{
    char *temp;
    int temp_length;


    if (!(*n))
    {
        return;
    }


    temp_length = strlen(t) + ONE;

    temp = malloc (sizeof(char) * temp_length);

    if (!temp)
    {
        printf("error when allocating memory to temp\n");
    
        *n = ZERO;
    
        free(temp);

        return;
    }

    memset (temp, ZERO, sizeof(char) * temp_length);
    
    strcpy(temp, t);

    

    for (; !isZero(temp); subChar(temp, ONE_CHAR, temp))
    {
        circularShiftRight(n);
    }


    free(temp);
}


void circularShiftRightIntT (char *n, int t)
{
    if (!(*n))
    {
        return;
    }
    
    
    
    for (; t; --t)
    {
        circularShiftRight(n);
    }
}


void randStr (char *str, int length, char min, char max)
{
    char *str_ptr;
    int ch;


    str_ptr = str;

    for (; length; --length)
    {
        ch = (rand() %  (max - min + ONE)) + min;

        *(str_ptr++) = ch;
    }


    *str_ptr = ZERO;
}