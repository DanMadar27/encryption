#ifndef FILES_OPERATIONS_H
#define FILES_OPERATIONS_H


#include <stdio.h>


// copies files contents to string
// and return length of file
int fileToString (FILE *src, char *dst, int max);


// copy string to file
void stringToFile (char *src, FILE *dst);

// copy string with given length to file
void stringToFileLength (char *src, FILE *dst, int src_length);


#endif