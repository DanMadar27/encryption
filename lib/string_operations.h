#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H


// reverse chars in given string
void reverse (char *str);


// copy reversed string of src in dst
void copyReverse (char *src, char *dst);


// store octal number representation of string src in dst
// each char in src will be 3 digits in dst
void stringToOctal (char *src, char *dst);

// stringToOctal with given length of src
void stringToOctalLength (char *src, char *dst, int src_length);


// store string representation of octal number src in dst
// and return length of dst
int octalToString (char *src, char *dst);


// return end of str
char * strEnd (char *str);


// return start of str without left zero chars
// with jump of jump variable
char * ignoreLeftZeroes(char *str, int jump); 


// return 1 if given sequence of chars are '0' chars,
// otheriwse - 0
char isZeroCharSequence (char *n, char *n_end);


// shifting chars 1 time to the right starting from str
// and stores char c in the previous addressess of shifted chars
void shiftCharsRight (char *str, int len);


#endif