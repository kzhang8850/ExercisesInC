/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void check_local(){
    int chicken = 0;
    printf ("Address of chicken is %p\n", &chicken);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *q = malloc(128);
    char *s = "Literal string";

    // given that these are right next to each other in memory, and var1 is global, i take it that main is next to the global part of the memory stack
    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);

    // from these two lines, it is clear that the heap goes up
    printf ("Address of p is %p\n", p);
    printf ("Address of q is %p\n", q);

    // from these two lines it is clear that the stack goes down
    printf ("Address of var2 is %p\n", &var2);
    check_local();

    // when checking it seems that the space between the two is 32 no matter what number i choose, and using 63 makes the space 64 which suggests that malloc, through additional testing, seems to block off memory in chunks of 16 (or some other number).
    void *a = malloc(32);
    void *b = malloc(32);
    printf ("Address of a is %p\n", a);
    printf ("Address of b is %p\n", b);


    return 0;
}
