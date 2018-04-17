/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

Read over and experimented with by Kevin Zhang

It would appear that at 5 children, the counter is almost always successfully incremented to the correct amount.

You can very easily tell that threads are runing concurrently because counter printouts will often
print the exact same number, meaning that two threads accessed the counter at the same time before
either one incremented, meaning that they're running concurrently, and with proper synchronization.

However, once you increase the number of children to something like 1000, you start to see
very obvious synchronization errors, the big one being that sometimes the final counter is no longer matching
the number of children, meaning that the threads are no longer always incrementing the counter
to the correct amount. This would mean that in that two threads are probably incrementing at
the same time, thus both accessing the value before either one increments, and thus both
increment to the same increased value, and by doing so losing one of the increments
to a synchronization error.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_CHILDREN 1000

/* Print an error message and exit.
*/
void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}

/* Call malloc and exit if it fails.
*/
void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

/* Structure that contains variables shared between threads.
*/
typedef struct {
    int counter;
} Shared;

/* Allocate the shared structure.
*/
Shared *make_shared()
{
    Shared *shared = check_malloc(sizeof(Shared));
    shared->counter = 0;
    return shared;
}

/* Create a child thread.
*/
pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

/* Wait for a child thread.
*/
void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

/* Code run by the child threads.
*/
void child_code(Shared *shared)
{

    printf("counter = %i\n", shared->counter);
    shared->counter++;
}

/* Entry point for the child threads.
*/
void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared();

    for (i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, (void *)shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    printf("Final value of counter is %d\n", shared->counter);
    return 0;
}
