## Homework 6

### C Exercises

Modify the link below so it points to the `ex06` directory in your
student repository.

[Here is a link to the ex06 directory in my repository](https://github.com/kzhang8850 /ExercisesInC/tree/master/exercises/ex06)

### Think OS Chapter 6 reading questions

**Memory management**

1) Which memory management functions would you expect to take constant time?
Which ones take time proportional to the size of the allocated chunk?

mallloc() generally doesn't depend on the size of the chunk, so it should be on average constant time, however it may take longer sometimes depending on the number of free chunks available. free() is constant time. calloc() depends on the size of the chunk because it must clear every byte in the chunk. realloc() can be constant depending on if the new chunk is smaller or if there is space available to expand the existing chunk. If it must find a brand new chunk of space and copy over the data, then its time becomes proportional to the size of the new chunk.

2) For each of the following memory errors, give an example of something that might go wrong:

a) Reading from unallocated memory.

Reading from an unallocated memory chunk might best case give you a segmentation fault because the system might detect the error. But more often the programs reads whatever happened to already be there, in which case the bytes stored there might be interpreted incorrectly, i.e. a string being read as a float, which results in a ridiculous number. Then passing that into a function can lead to strange outcomes.

b) Writing to unallocated memory.

Writing to unallocated memory can lead to long-term silent errors, where a long time might pass before the value is read, and then later on cause problem far down the line from where the original problem began. In this case finding the source of the problem might be very difficult.

c) Reading from a freed chunk.

Reading from freed chunk is considered accessing a piece of memory that technically shouldn't be accessed and is similar to an unallocated piece, but because it is on the heap already since it was allocated before, there is a higher possibility that you will enter undefined behavior, at which you most likely will read something "correct" assuming that the freed chunk hasn't yet been returned to the system or recycled. This will then cause strange behavior in your program because it won't error out but will proceed with nonsense values. Another better scenario is that it will read an invalid value and then break.

d) Writing to a freed chunk.

Writing to a freed chunk is also considered similar to an unallocated piece, but again since it's on the heap, there is a higher probability it will not segmentation fault and enter undefined behavior, where a value will be written to a place that cannot be read. Assuming that the program doesn't already break due to an invalid write, some other part of your program will most likely be missing a value since a written value wasn't put in a spot that can be accessed, and thus cause strange behavior in your program. There is a small possibility perhaps that one could write and read from the same freed chunk of memory, and maybe that will illegitimately work, but if that chunk is ever allocated again by another part of the program, then you're accessing the chunk from two different sources doing different things, which will ruin the output of the program.

e) Failing to free a chunk that is no longer needed.

If you allocate a chunk of memory and then never free it, then that's a memory leak. If your program then runs for a long time and continually leak memory, its total memory can increase indefinitely, so either your system will run out of physical memory, or your virtual memory will run out, or your process's memory limit will be reached. In all these cases, malloc will eventually return NULL, then trying to utilize with a NULL structure will probably error out your program in some fashion. Either way, you will be consuming way more memory than you would ever need which might break your program.


3) Run

```
    ps aux --sort rss
```

to see a list of processes sorted by RSS, which is "resident set size", the amount of physical
memory a process has.  Which processes are using the most memory?

Trying this on a freshly booted up Ubuntu partition that is idle without any major programs running, the processes using the most memory are python3 and the update manager (i think because I had pending updates to download that were sitting on my computer, from the software updater program), followed by compiz and gnome as close 2nd and 3rd. Then comes Xorg, nautilus, and other daemons terminals, subprocesses, and graphics processes (unity) needed for Ubuntu to run. The moment I run Chrome, it instantly takes up the top 5 most memory-intensive process spots on my computer.

4) What's wrong with allocating a large number of small chunks?  What can you do to mitigate the problem?

The problem with allocating a large number of small chunks is that boundary tags and free list pointers take up space, and these data structures reside naturally in heap memory chunks. In fact a minimum space required for a chunk is 16 bytes due to this space overhead on the heap chunks. A lot of these small chunks together then is very inefficient in terms of space usage for your data and personal variables, as probably like half of it goes to just making and allocating all your chunks' internal data structures. A way to mitigate the problem is to then just allocate all your tiny memory into arrays, which is more efficient in holding a large number of your small structures together in the heap.

If you want to know more about how malloc works, read
[Doug Lea's paper about dlmalloc](http://gee.cs.oswego.edu/dl/html/malloc.html)
