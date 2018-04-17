## Homework 10

### C Exercises

Modify the link below so it points to the `ex12` directory in your
student repository.  That's right, Homework 10 is to do Exercise 12.

[Here is a link to the ex12 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex12)

### Think OS Chapter 10 reading questions

1) What does it mean to say that a data structure is thread safe?

Thread safe means that two or more threads can access the queue at the same time without problems. That is, multiple concurrent accesses should not leave the data structure in a broken, inconsistent state. The data structure should have implementations and protections in place to prevent synchronization errors.

2) In the circular buffer implementation of a queue, why is the maximum number of elements in the queue `n-1`,
if `n` is the size of the array?

The maximum number of elements is n-1 because of the way that queue is implemented. A queue is considered "empty" if its next_in and next_out indices land on the same index, and in terms of adding elements, an item will be added into the queue at the position of next_in, and then next_in will increment by one. However, when the next_in index wraps around and gets close to the next_out index again, a queue is considered "full" when the next_in index, the index where the next item would be placed but at the time doesn't have an item yet, is one behind the next_out index. This is because if a final item were to be placed into the queue, then queue_push would increment the next_in index back onto the next_out index, satisfying the condition that it is empty when in fact it's full. Thus the space right behind the next_out index is always empty, meaning that the size of the queue is always n-1, where n is the size of the array.

3) If there is no mutex to protect the queue, give an example of a sequence of steps that could leave
the queue in an inconsistent state.

If for example, there are two threads that are both working concurrently on one queue, and both are pushing into the queue using queue_push. Without mutex, it's very much possible that thread A can grab queue->next_in and assign an item there, and then thread B can also grab queue->next_in before thread A could increment it, and then also assign an item there. Then both threads could increment the queue->next_in index sequentially. This would mean that the item thread A placed is now overwritten by the item thread B placed, so it doesn't exist in the queue, and the spot after the item placed by thread B will now be skipped because despite overwriting the same spot, both threads still incremented queue->next_in. Very evidently, this would lead to an inconsistent, broken state.

4) When a thread calls `cond_wait`, why does it have to unlock the mutex before blocking?

If the thread doesn't unlock the mutex before blocking, the its execution will halt, but because it's currently holding onto the mutex no other thread can access that process's queue, so nothing would happen to the queue, the thread that blocked and called cond_wait will never be able to change the status that caused it to call cond_wait, and so the entire process just freezes. Thus the mutex must be unlocked before blocking to allow for some other thread to access the queue and change the status quo and allow the original thread to unblock at some point in the future and continue on with the program.

5) When a thread returns from `cond_wait`, what do we know is definitely true?  What do we think is probably true?

When a thread returns from cond_wait, we definitely know that the thread has locked the mutex, so it's safe to access the queue. However, it's possible that due to an intercepted signal, where a third thread came in, took the mutex before this thread could, changed the queue somehow, and then unlocked the mutex for this thread to take, the condition itself might not be true, but it probably is, as those scenarios are more often rare than not. Therefore the mutex is a definite, and the condition itself is probable but not guaranteed.

6) What happens if you signal a condition variable when there are no waiting threads?

If there are no threads waiting on the condition variable that was signaled, then the signal just has no effect. Nothing happens.

7) Do you have to lock the mutex to signal a condition variable?

No you don't have to lock the mutex to signal a condition variable. The logical implementation would be that threads that are waiting on that signal are blocked by cond_wait, which means that even if the mutex is unlocked those threads can't run because the signal hasn't been sent to unblock them. Therefore it's very possible to unlock the mutex first and then signal the condition variable. In other words, both unlocking of the mutex and signaling of the condition variable must occur for another thread that logically waiting for that signal to run, and it doesn't matter what order those two commands are executed because both are required for the other thread to run.

8) Does the condition have to be true when you signal a condition variable?

Not necessarily, it just means that it might be true. Logically speaking, it looks like conditions don't have any sort of specific conditional themselves that check for if a certain condition tied to them is true or not; rather, they just send out a signal on that Cond structure with the assumption that it's going to be true when calling cond_signal and false when calling cond_wait. The connection between true/false and the variable itself is implicit, based on the mind of the programmer in the way it is used. In terms of the code implementation, there is no explicit connection between a Cond structure and the condition it relates to.
