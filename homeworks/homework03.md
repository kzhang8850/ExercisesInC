## Homework 3

### C Exercises

Modify the link below so it points to the `ex02.5` directory in your
student repository.

[Here is a link to the ex02.5 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex02.5)

### Think OS Chapter 3 reading questions

### Virtual memory

1) The Georgian alphabet has 33 letters.  How many bit are needed to specify a letter?

You would require 6 bits to specify a letter. 5 bits would only allow for 2^5 = 32 possibilities, which is too small for
the the Georgian alphabet; 6 gives you 64 possibilities, so you have more than enough.

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  
Ignoring the details of the encoding scheme, how many different characters can be represented?

If a character representation can take up 32 bits, then that means in total there would be 2^32 = 4294967296 different characters
possible.

3) What is the difference between "memory" and "storage" as defined in *Think OS*?

"Memory" is considered the volatile memory in "main memory", usually related to random access memory (RAM). Most of the data in processes runs on "memory", and
when the computer shuts down the contents in this memory are lost. In casual use, this is generally RAM.

"Storage" is considered the nonvolatile memory stored on a physical drive, usually a hard disk or solid state drive. When processes read and write files or other
such data, they usually store this information in "storage", and when a computer shuts down the memory in "storage" is retained, thus they are
good for long-term storage of data and information. In casual use, this is HDD and SSD.

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes?

GiB is a gibibyte, which is 2^30 bytes and used as a metric for RAM. GB is a gigabyte, which is 10^9 bytes and used for HDD/SSD. For historical
reasons memory is measured in binary units, and storage in decimal units. In terms of percentage difference, 2^30 = 1073741824 and 10^9 = 1000000000, so
their percentage difference is ~7.2%.

5) How does the virtual memory system help isolate processes from each other?

The virtual memory system utilizes virtual addresses that map to the actual physical addresses in memory. Programs never have to deal with the physical addresses
or know how much is available. When a program read or writes a value in memory, it generates a virtual address. The hardware and operating system then translate this
to a physical address, and then access that address in main memory. This translation is done on a per-process basis, so no two processes can reach the same physical address in memory. In this way, processes cannot access data belonging to another process, because there is no way it can generate a virtual address that maps that another process's allocated memory.

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?

The stack and heap are the most "dynamic" of memory, as the text segment, and statics segment don't really change. In this sense, it makes sense to allocate the unchanging memory near the bottom of memory addresses, as their required space is known and shouldn't take up too much, and then leave the remaining space closer to the higher memory addresses for the dynamic memory in the stack and heap, as their space as compile time is not as easily quantified as the text and statics segment. Since the stack grows in size with variables and functions, and the heap grows in size usually with things like malloc, then in order to make sure that they each have adequate space to grow during run-time, the logical conclusion would be to put them on opposite ends of the finite address space and then grow towards each other. Technically speaking, the stack and heap could've been switched in their sides, but the basic premise is that they potentially need the most memory, and in an effort to give both as much memory as possible while making sure they don't overwrite each other, put them on opposite ends of the address space, preferably near the top side as the non-volatile memory can safely be held in lower memory addresses.

7) What Python data structure would you use to represent a sparse array?

To represent a sparse array, you can use a sparse matrix in Python. This can be built in many ways, either with a dictionary, or list of lists, or a specialized array representation known as compressed sparse row or Yale format. If you were allowed to use libraries, scipy has built-in data structures for sparse arrays. Things like associated arrays also become easily implemented with the use of libraries.

8) What is a context switch?

A context switch is the mechanism by which the operating system can interrupt a running process and save its state so that it can then run another process. Processes each have page tables, so the MMU must work with the operating system to ensure proper process to page table pairing. In newer systems this has optimized such that the MMU can hold page tables from multiple processes and thus doesn't have to switch page tables every context switch.
