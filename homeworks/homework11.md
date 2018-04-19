## Homework 11

### C Exercises

Modify the link below so it points to the `ex11` directory in your
student repository.

[Here is a link to the ex11 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex11)

### Think OS Chapter 11 reading questions

1) Why is is a bad idea to pass a `sem_t` as a parameter?

A `sem_t` behaves equivalently to that of a structure, therefore when assigned to a variable it will
copy all of its contents. The act of copying with POSIX library structures like threads, mutexes, and
Semaphores is undefined behavior, thus it is a better idea to initialize it as a pointer and pass it
by reference.

2) When you use a Semaphore as a mutex, what should its initial value be?

The initial value should be 1 to indicate that the initial state of the mutex is unlocked, that is, one thread
can pass through the Semaphore without blocking.

3) Can you think of another use for a Semaphore where you might use a different initial value?

You can use a Semaphore to keep track of the number of items in a queue, which in terms of a
producer/consumer problem would also mean to keep track of the number of consumer threads that can pop off an item
without blocking. This would initially be set to 0 upon creation of the queue, as at first there would be
nothing in the queue and thus no consumer should be able to run.

4) In my solution to the producers-consumers problem using Semaphores,
what does it mean if the value of `queue->spaces` is `3` at some point in time?

If `queue->spaces` is ever '3', then that would mean that there are 3 spaces left that are
empty in the queue, or 3 more potential producer threads that can execute `queue_push` without
blocking.

5) What does it mean if `queue->spaces` is `-3`?

If `queue->spaces` is ever '-3', then that would mean that technically speaking there are -3 empty spaces left in the queue,
because producer threads are attempting to push more items into the queue than the queue can hold. In terms of
actual threads, this would most likely be the scenario where a thread pushed in an item to make `queue->spaces` 0,
meaning that there are no empty spaces left and the queue is full, and then afterwards 3 more producer threads
attempted to execute, but then they all called `sem_wait` only to find a negative return, and so they all block,
waiting for a signal from `queue_pop`. Once a consumer thread calls `queue_pop`, then a signal will wake one of the
blocked producer threads, and `queue->spaces` will be at -2. The queue will most likely be more or less full for quite some time, as after
the blocked thread wakes and executes, the queue will once again be filled, and there are still 2 producer threads
waiting on a signal to add still more items into the queue.

6) Why doesn't `queue_pop` have to use `queue_empty` to check whether the queue is empty?

The `queue_pop` function doesn't need to because it's using a Semaphore to perform the same functionality. At
the very beginning of the function it will call `semaphore_wait` on `queue->items`, which will decrement the
`items` Semaphore. `items` is meant to represent the number of items in the queue, or the number of consumer
threads that can call `queue_pop` without blocking. In other words, if `items` is set at 0, then that
means that the queue is empty. If another consumer thread were to then call `queue_pop`, then it would call `semaphore_wait` on
`queue->items`, which will push the `items` Semaphore to a negative number if the queue is indeed empty. At this point
the consumer thread will block, until a producer pushes an item onto the queue and signals the waiting thread. If instead the
`items` Semaphore just decremented to a nonnegative number, then that means that the queue is not empty, and the consumer thread
can move forward with acquiring a mutex and popping off an item from the thread. This behavior is equivalent to
checking if a queue is empty using `queue_empty`.

7) Any problem that can be solved with Semaphores can also be solved with mutexes and condition variables.
How can you prove that that's true?

To prove that any problem that can be solved with Semaphores can also be solved with mutexes and condition variables,
you can implement a semaphore using condition variables and mutexes. This would then prove that any functionality a
semaphore can provide can likewise be provided by condition variables and mutexes.

8) What is Property 3?  Hint: see *The Little Book of Semaphores*,
[Section 4.3](http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf).

Property 3 is that if there are threads waiting on a Semaphore when a thread executes a signal, then one of the waiting
threads has to be woken. This effectively prevents starvation, which is then a thread or set of threads never run and are
indefinitely waiting while other threads continually proceed. As an example, a problematic behavior that can occur with threads
and Semaphores is that a thread could signal to threads that are waiting on a Semaphore, then keeps running, waits on the Semaphore,
and gets its own signal back, thus effectively starving out the other waiting threads. Property 3 is in place to prevent
such starving behavior.
