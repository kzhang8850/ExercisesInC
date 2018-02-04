/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/*
This code is meant to simply initialize an int array of 42, then send it back to main as an int pointer, call a dummy function that shouldn't do anything useful, and then print the original 42 array.

Got a warning on compilation that says that the address of array was returned. This seems to be warning you that you're returning  a memory allocation that is going to be scrapped because the function will close.

When run, the memory addresses of the array in foo and the array in bar are the exact same, when they shouldn't be. In addition, I got weird output from the printf in main. This is because of the way the stack works. When a function is called, the stack begins to allocate memory for the variables used in the function, like i and array in foo. But once the function ends, that memory is recycled or garbage collected for use later on in the program. In a sense, the stack acts very much like a stack, going down to allocate memory for functions and then going back up to collect the memory when they're done. Thus, when the foo function was over, the array was recycled, and the "marker" for memory allocation resets back to the position before the function, so that's why bar uses the same memory address for its array variable. The output is then printed out as gibberish because that variable no longer points to any meaningful memory allocation, as it was recycled once foo finished. Even without the print statements, the output is still messed up, albeit different values now.

The fix is to use malloc, which will put the array variable into the heap. The heap isn't garbage collected upon function termination like the stack is, and persists as long as the program is running. Thus variables of interest should always be put in the heap (or declared in main), such that they can be used elsewhere in the program.

*/
// basic includes
#include <stdio.h>
#include <stdlib.h>

// defined global variable 5
#define SIZE 5

/*
meant to initialize an int array named 'array' and set all elements to 42 int.
then returns the array as an int pointer variable
*/
int *foo(){
    int i;
    int *array = malloc(SIZE*sizeof(int));
    // int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

/*
meant to initialize an int array named 'array' and set elements to 0-4 in ascending order
*/
void bar() {
    int i;
    int array2[SIZE];

    // printf("%p\n", array2);

    for (i=0; i<SIZE; i++) {
        array2[i] = i;
    }
}

/*
runs foo first, and sets an int pointer named 'array' as the return value of foo
then runs bar, and prints out the contents of its array pointer 'array'
*/
int main()
{
    int i;
    int *array = foo();
    printf("%p\n", array);
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
