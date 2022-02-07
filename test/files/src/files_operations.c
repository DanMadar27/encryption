#include "../../../res/numbers.h"
#include <stdio.h>
#include <stdlib.h>


int fileToString (FILE *src, char *dst, int max)
{
    FILE *src_ptr;
    char *dst_ptr;

    int src_length;


    src_ptr = src;

    dst_ptr = dst;

    src_length = ZERO;

    while (max && !feof(src_ptr))
    {
        *(dst_ptr++) = fgetc(src_ptr);

        --max;        

        ++src_length;
    }


    if (!max && !feof(src_ptr))
    {
        printf("error : source file is bigger than destination string\n\n");


        if (fclose(src))
        {
            printf("error when closing file\n\n");
        }


        exit (EXIT_FAILURE);
    }

    // fgetc return EOF in end of file
    // so put 0 in end of string
    // and subtract 1 from src_length
    
    *(--dst_ptr) = ZERO;
    
    --src_length;

    return src_length;
}


void stringToFile (char *src, FILE *dst)
{
    char *src_ptr;
    FILE *dst_ptr;

    dst_ptr = dst;

    for (src_ptr = src; *src_ptr; ++src_ptr)
    {
        fputc(*src_ptr, dst_ptr);
    }

}


void stringToFileLength (char *src, FILE *dst, int src_length)
{
    char *src_ptr;
    FILE *dst_ptr;

    src_ptr = src;
    dst_ptr = dst;

    for (; src_length; --src_length, ++src_ptr)
    {
        fputc(*src_ptr, dst_ptr);
    }
}