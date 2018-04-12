/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

Completed by Kevin Zhang

Softsys Spring 2018

I edited the code to show that two processes do not share memory together, aside
from the coming out of the same code segment. When fork() is used, it does a
duplication on the process including all of its program states, so the static, heap, global,
and stack segments are all copied and relocated elsewhere in another part of virtual
memory. Thus a parent process and a child process look exactly the same with all of the
same variables and states etc., with the exception that their pids upon call of
fork() are different, and they do not share any memory segments together.

The modified code below proves that is so.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;
int global_var = 4;  // global variable to check for sharing between processes
int main();

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}

/*
change all of the variables made in the parent process in the child process.

i: the child process number when it was made
x: the heap variable
y: the static variable
*/
void child_code(int i, int *x, int *y)
{
    sleep(i);
    printf("Hello from Child %i\n", i);
    *x += 4;
    *y += 6;
    global_var += 7;
    printf("Main's address is %p\n", main);
    printf("Child's address is %p\n", child_code);
    printf("Child's heap var is now %i\n", *x);
    printf("Child's static var is now %i\n", *y);
    printf("Child's global var is now %i\n", global_var);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    /*
    make a bunch of variables, one from the heap, the stack, the statics, and the
    globals. then print them to show what they are now, so that we can reference
    them later once we attempt to change them
    */
    static int y = 5;
    int *x = malloc(sizeof(int));
    *x = 3;
    int a = 1;

    // note that I printed the main and child_code function's addresses, and
    // proved to be the same between the two processes, even when also called inside
    // the child process (see child_code)
    printf("Main's address is %p\n", main);
    printf("Child's address is %p\n", child_code);
    printf("Original heap var is %i\n", *x);
    printf("Original static var is %i\n", y);
    printf("Original global var is %i\n", global_var);
    printf("Original stack var is %i\n", a);

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }


        /* see if we're the parent or the child */
        if (pid == 0) {
            /*
            here we will change the values of the variables made above in the child
            process, in hopes that it will cause a change in the parent as well
            */
            child_code(i, x, &y);
            a++;
            printf("Child's stack var is now %i\n", a);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }

    /*
    here we once again check all the values in the various memory segments to see
    if their values have changed corresponding to the changes made in the child
    process. and the answer is no, none of them did. They are the exact same
    as they were in the beginning, despite the child process changing the exact
    same variables. This proves that with the exception of the code segment, all of the
    memory segments between two processes from fork() are different
    */
    printf("Parent's heap var is now %i\n", *x);
    printf("Parent's static var is now %i\n", y);
    printf("Parent's global var is now %i\n", global_var);
    printf("Parent's stack var is now %i\n", a);

    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
