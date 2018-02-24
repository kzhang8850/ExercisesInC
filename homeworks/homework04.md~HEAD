## Homework 4

### C Exercises

Modify the link below so it points to the `ex03` directory in your
student repository.

[Here is a link to the ex03 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex03)

### Think OS Chapter 4 reading questions

**Files and file systems**

1) What abstractions do file systems provide?  Give an example of something that is logically
true about files systems but not true of their implementations.

The file system provides the abstraction that a file system maps from file names to a stream of bytes. In addition, file names are usually strings with a hierarchical structure in which top-level directories lead to a series of subdirectories to a specific file. In contrast, persistent storage is stored in blocks of memory, which are laid out in sectors, and then tracks, and then circles on platters, so the hierarchical structure is incredibly more complex.

2) What information do you imagine is stored in an `OpenFileTableEntry`?

An OpenFileTableEntry most likely holds a pointer that references the character in the file that is currently of interest. In addition, it might also hold a record of all the memory blocks that are associated with the file, that way once the memory block that the pointer is on is completely read, it can find the next memory block to be loaded, and then move the pointer to begin reading the contents of that memory block.

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?

One way is block transfers, which is that it keeps the processor busy by having it do work on other blocks or execute instructions during the time it takes to load a byte from the disk. Another way is prefetching, which is when the operating system predicts that a process will read a block and start loading it before it is requested. A third way is buffering, where the block is held in memory and modified several times before writing it to disk once, thus lowering the number of times the slow performance of disk must be utilized. A fourth way is caching, where the operating system keep a copy of the block in memory to handle future requests at memory speed.

4) Suppose your program writes a file and prints a message indicating that it is done writing.  
Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the
file you wrote is not there.  What happened?

In this case, it's highly likely that the "done writing" actually meant it had finished writing to a cache in memory, and not actually to permanent storage. Buffering is a similar problem that could also cause this issue. In that case, since your saved changes are all still in memory because the operating system is trying to limit the number of times it calls on the disk, when your computer reboots, it's very possible that it shut down while all your changes were actually still in memory, so your data might've been lost because it was in a cache and not yet on disk.

5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?

One advantage of FAT over inode is that FAT is simple yet robust. Basically being a link list of sorts, it is fairly easy to implement and easy to maintain, yet well-designed enough to be able to scale and deliver strong performance. Inode in this sense is far more complicated and probably makes the implementation more heavy-weight and difficult, as the indirection blocks take up space and make the system more confusing to understand. That being said, one advantage of inode over FAT is that inode can scale much more easily and take on much larger file systems much more easily then FAT, as the indirection blocks give it several magnitudes more capability in storing indices and indices of indices etc., whereas for FAT that same process would take a lot more diving down the linked list to find the next block. Performance is probably more reliable and faster for inode, which is also why it's used more often these days.

6) What is overhead?  What is fragmentation?

Overhead is the data structures used by the block allocator to be able to function as a block allocation system when assigning available blocks and re-allocating them. Fragmentation is the unused space when some block are left unused or only partially used.

7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?

Reusing the same principle makes it easy for programmers because they only have to learn one API and also makes programs more versatile because programs with an original intended I/O can also be easily utilized to work with data coming from pipes and other sources besides the original. A potential downside is then everything uses the same general framework of I/O, which can create security flaws that are widespread and difficult to solve, kind of like how lack genetic variation is bad for a species due to potential epidemic wipeout. Another potential downside is that innovative progression of  such low-level structures  become harder when everything is abiding by the same principle. If someone were to create a revolutionary new communication abstraction that is way better than the stream of bytes abstraction, then that would mean that everything would have to make shift, which might be very cumbersome and in some cases might break that platform higher-level structures depending on implementation.

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.  
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).  
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).
