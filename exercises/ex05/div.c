/*  Code for Think OS.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union FloatIntUnion {
    float f;
    uint32_t i;
} b;

/* Get the exponent part of a float.
*/
uint32_t get_exponent(float x) {
    b.f = x;
    uint32_t mask = 0xff;
    uint32_t expon = (b.i >> 23) & mask;
    return expon;
}

/* Divide a float by a power of two.
*/
float div_by_pow_2(float x, int n)
{
    uint32_t exp = get_exponent(x);
    exp -=n;
    b.f = x;
    uint32_t sign = (b.i >> 31) & 1;
    uint32_t coef = b.i & ((1<<23) -1);
    b.i = (sign<<31) | (exp <<23) | (coef);
    return b.f;
}

int main() {
    float y = div_by_pow_2(32.0, 5);
    printf("%f\n", y);
    return 2;
}
