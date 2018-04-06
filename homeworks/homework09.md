## Homework 9

### C Exercises

Modify the link below so it points to the `ex09` directory in your
student repository.

[Here is a link to the ex09 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex09)

### Think OS Chapter 9 reading questions

1) Why does each thread have its own stack?

Each thread has its own stack because threads want to be ale to call functions without interfering with each other. In addition, threads generally don't want to be able to access each other's local variables for fear of messing up the flow of execution for a given thread (i.e. a thread might a certain a variable and expect it to be x but if a different thread randomly changes it to y then the original thread will be confused).

2) What does the gcc flag `-lpthread` do?

The flag allows you to compile the Pthread library in gcc. The -l provides the name of the pthread library which gcc should make sure to link to the .c file of interest so that it may use the functionality in that library in its own code.

3) What does the argument of `pthread_exit` do?

The argument is a void pointer value that can be passed to any thread that joins with the now terminating thread. In other words, if a thread waits for another thread to complete before continuing, then this value may be used to pass something to the blocked thread to tell it to, say, resume running once the other thread has terminated through pthread_exit.

4) Normally the same thread that created a thread also waits to join it.
What happens if another thread tries to join a thread it did not create?

If another thread tries to join a thread it did not create, in general that will work fine. However, if a nonparent thread and a parent thread both join a child thread, it's possible that upon termination the child thread will not send any feedback to the nonparent thread, so that thread may be blocked indefinitely because it's not receiving any signal to resume. This is possible because pthread_exit might only return a value to one joined thread, as its only meant to be joined by a single thread, therefore the second would never get a signal to resume. Alternatively, it's possible that it will attempt to join the created thread but that thread had already terminated, either through the real parent or itself, and thus the  other thread will just continue on as if the join never existed.

5) What goes wrong if several threads try to increment a shared integer at the same time?

This would be a synchronization error, where depending on the timing it's possible for all of the threads to actually access the integer value and increment it at randomized (and sometimes the same) instances, so in the end the integer might best case be incremented a few times but less than the number of attempted increments, or potentially only incremented once or twice if they all access the value before any threads increment and then all increment the same value up one and return, so then the final value is literally just one above what it originally was. It's also entirely possible that all increments will go through properly, but if a thread attempts to read the integer or access it at any time while it's being overwritten then it will most likely get a value that doesn't agree with the flow of execution, or a nonsensical value period. Threads can be interrupted at different points, so the sequence of events will be different and randomized each time, leading to data races as described above, and that makes debugging and understanding what your code is doing really tricky. This is why things like mutex are useful.


6) What does it mean to "lock a mutex"?

Locking a mutex means barring all other threads from accessing the locked mutex while a given thread is accessing it. This means that the threads will line up to execute the program one at a time, so they can't interfere with each other.
