## Homework 6

### C Exercises

Modify the link below so it points to the `ex06` directory in your
student repository.

[Here is a link to the ex07 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex07)

### Think OS Chapter 7 reading questions

### Caching

1) What happens if a program writes a new value into the program counter?

If a program writes a new value to the PC, then the execution point of the program will jump to that written value, which may be incremental (moving down one line in the program), or a jump to another part of the program (an if else statement).


2) What is the fundamental problem caches are meant to solve?

Caches are meant to solve the problem where transferring data between the CPU and main memory takes far too long, and thus cache exists to prevent constantly having to wait for memory to access data in a process or program. In a CPU, an instruction can be initiated every 0.5 ns, but accessing memory can take up to 10 ns, which is far too slow to keep up. Caches only take 1-2 ns, which is much closer to a 1-1 ratio with instruction speeds. This is also known as the memory bottleneck.

3) If cache access time is 1 ns and memory access time is 10 ns, what is the average
access time of a program with hit rate 50%?  How about 90%?

With hit rate 50%, the access time would be about hT_h + mT_m = .5 * 1 + .5 * 10 = 5.5 ns

With hit rate 90%, the access time would be about hT_h + mT_m = .9 * 1 + .1 * 10 = 1.9 ns


4) The book gives several examples of programming language features, like loops, that tend
to improve locality in the access pattern of instructions and/or data.  Can you think of other examples?  
Or counter-examples that might decrease locality?

A struct that is continuously used and updated, perhaps as an agent in an environment whose state constantly changes, is considered temporal locality because the struct's fields are continuously and frequently being accessed. The struct itself is considered spacial locality because all of its attributes are declared and accessed all at once in the same sequential period. A linked list would decrease spacial locality because it is completely non-contiguous and updating the linked list would further fragment the space used. A temporary variable can potentially be considered bad for temporal locality because it may only be called once to hold onto a piece of data for a small period of time and then for the majority of the program it isn't used.

5)  If you refactor a program to improve locality, would you say the program is "cache aware"?  Why not?

No because refactoring to improve locality is not the same as being "cache aware". Cache aware is designing your program to be tailor fit to your specific hardware's cache size, block size, etc. This then allows it to run at optimal speeds and utilize its fast cache speeds as much as possible. Improving locality kind of moves in that direction as you're improving your hit rate in using the cache's speed by improving your code, but it's not as exact and optimized as being cache-aware, which is going all-out for performance.

6) See if you can estimate the cost of a memory cache by comparing the prices of two similar CPUs with
different cache sizes.

To find the cost of a memory cache, we can compare two CPUs with similar specs but different cache sizes, and then divided the difference in price by the difference in cache size for a rough estimate. Looking at Intel's newest line of CPUs, an i7 8700K with 12 MB of Cache is $329, whereas a tier down at i5 8600K with 9 MB of Cache is $229. Their other specs are fairly comparable with some small differences. Doing the math leads to a result of (329-229)/(12-9) = ~$33/MB of cache as an approximate upper bound, which even as a ball park estimate is pretty expensive.

7) Why are cache policies generally more complex at the bottom of the memory hierarchy?

Cache policies are more complex near the bottom because they are slower and thus have more "time" to perform more complicated operations in a policy. Well designed policies can make a big difference, and thus policies that have the time to undertake a more complex framework should have a better designed policy in comparison to policies higher on the hierarchy  that must be fast and thus must be simple.

8) Can you think of a strategy operating systems could use to avoid thrashing or recover when it occurs?

One strategy would be to block and kill processes until the system is responsive again when paging spikes suddenly. Another more far-fetched strategy would be to use or bring in another cache for storing page data whose pages are often swapped between processes, which would then allow for much faster access to a set of data that is constantly being swapped in and out of pages used by multiple processes.
