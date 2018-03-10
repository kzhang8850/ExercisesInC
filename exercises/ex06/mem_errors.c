/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

/*
Edited by Kevin Zhang SoftSys Spring 2018

I have fixed all the errors in memory leakage. The code doesn't necessarily
do anything useful, which I don't believe was the point of the exercise, but at least it doesn't leak memory anymore.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    int never_allocated;
    never_allocated = 1;
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    array1[1] = never_allocated;
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, 1);
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    read_element(array2, 1);
    read_element(array2, 99);

    free(use_after_free);

    *never_free = 17;
    free(never_free);
    free(free_twice);
    free(array2);

    return 0;
}
