#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H


// returns 1 if a is smaller than b, otherwise - 0
char isSmaller (char *a, char *b);

char isSmallerChar (char *a, char b);


// returns 1 if a is greater than b, otherwise - 0
char isGreater (char *a, char *b);


// returns 1 if n equals 0, otherwisze - 0 
char isZero (char *n);


// calculate addition of two octal numbers represented as strings
// and stores the result in "result" parameter
// calculating a + b
// domain of parameters:    a >= 0,  b >= 0
void add (char *a, char *b, char *result);

void addChar (char *a, char b, char *result);


// calculate subtraction of two octal numbers represented as strings
// and stores the result in "result" parameter
// calculating a - b
// domain of parameters:    a >= 0,  b >= 0  ,  a > b
void sub (char *a, char *b, char *result);

void subChar (char *a, char b, char *result);


// calculate product of two octal numbers represented as strings
// and stores the result in "result" parameter
// calculating a * b
// domain of parameters:    a >= 0,  b >= 0
void mult (char *a, char *b, char *result);


// calculate division of two octal numbers represented as strings
// and stores the result in "result" parameter
// the function does not calculates remainder
// calculating n / divisor
// domain of parameters:    n >= 0,  divisor > 0
void divN (char *n, char *divisor, char *result);


// calculate modulo operation of two octal numbers represented as strings
// and stores the result in "result" parameter
// calculating n % m
// domain of parameters:    m > 0
void modN (char *n, char *m, char *result);


// calculate xor between two octal numbers represented as strings
// and stores the result in "result" parameter
// calculating a ^ b
void xor (char *a, char *b, char *result);


// circular shift bits in n 1 time left
// n is octal number represented as string
void circularShiftLeft (char *n);


// circular shift bits in n 1 time right
// n is octal number represented as string
void circularShiftRight (char *n);


// circular shift bits in n t times left
// n is and t are octal numbers represented as strings
void circularShiftLeftCharT (char *n, char *t);

void circularShiftLeftIntT (char *n, int t);


// circular shift bits in n t times right
// n is and t are octal numbers represented as strings
void circularShiftRightCharT (char *n, char *t);

void circularShiftRightIntT (char *n, int t);


// store random number in given string with given length
// with numbers between min and max
void randStr (char *str, int length, char min, char max);


#endif