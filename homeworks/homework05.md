## Homework 5

### C Exercises

Modify the link below so it points to the `ex05` directory in your
student repository.

[Here is a link to the ex05 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex05)

### Think OS Chapter 5 reading questions

**Bits and bytes**

1) Suppose you have the value 128 stored as an unsigned 8-bit number.  What happens if you convert
it to a 16-bit number and accidentally apply sign extension?

When you accidentally apply sign extension, you are just copying the sign bit into the new bits that have been allocated for this number. In the specific case of 128 as an unsigned number, that means it's positive, so it will just add a bunch of 0's to the existing sequence of bits.

2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator.
Try it out and confirm that the result is interpreted as -12.

  11111010
^ 00001110

= 11110100

3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a
sign bit or two's complement?

One reason might be it was originally just easier to code into the system because all you had to do was add 127 for an 8 bit number since -127 is the lowest possible, and then just look at the threshold of the bias to determine a positive or negative exponent. Another correlated reason might be that in this way it's easier to do order comparisons between two positive numbers by simply comparing their bit strings lexicographically. In order for easy comparisons to occur between numbers, smaller exponent numbers must be able to be compared to similarly small exponents first before larger ones, and bias makes this very easy, whereas two's complement messes with the natural ordering of the numbers on a scale, thus requiring more work. A third small additional reason is that in zero is lifted above just an all zero representation and made into a bit string representation, which again might be easier to use when utilizing floating points. Overall, convenience might be the big answer.

4) Following the example in Section 5.3, write the 32-bit binary representation of -13 in single precision
IEEE floating-point.  What would you get if you accidentally interpreted this value as an integer?

32-bit binary representation of -13 is 11000001010100000000000000000000

When you accidentally interpret this value as an integer, you will forego the various sections of sign, exponent, and mantissa, and just read the bit string straight up as if it was a 32 bit integer, which would then evaluate as a really large number that isn't anything close to -13.

5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.  
As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one
character at a time.  This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.

```
void to_upper(char chicken[]){
    for(int i = 0; chicken[i] != '\0'; i++){
        chicken[i] ^= (1<<5);
    }
}
```
