## Homework 2

### C Exercises

Modify the link below so it points to the `ex02` directory in your
student repository.

[Here is a link to the ex02 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex02)

### Think OS Chapter 2 reading questions

For each of the reading questions below, write answers in the form of
a clear, concise, complete sentence or two.

1. Give a real-world example of virtualization (ideally not one of
the ones in the book).  What is abstractly true about the system that
is not literally true about the implementation?

An example of virtualization is a smart watch like a Fitbit and cloud computing. The smart watch gives the impression of showing you the number of miles walked, your calories burned, your notifications, etc., as if all of that information and calculations were performed in your device memory, but the reality is your device is connected via bluetooth/WiFi to a server belonging to the company, which in turn might be connected to other servers which are connected to other servers and so on. It is this giant complex network of servers across the world that can calculate your data in the "cloud". The reality is that the smart watch's processing capability is actually quite limited, but it's ability to connect to servers coupled with a nice display make it seem as if the smart watch is truly smart and infinitely powerful.

2. What is the difference between a program and a process?

A process is a software object that represents a running program. A process can contain the program itself, but also the data associated with the program, the state of IO operations, and hardware information that the program uses. A program is essentially a script that performs a function on your system, and a process is a mechanism that isolates programs from each other so that unwanted interactions in the system can be prevented.

3. What is the primary purpose of the process abstraction?

The primary purpose is to allow users and other programmers to use powerful and complicated systems without having to know about the details of their implementation. In other words, it is representing something complicated as something simple.

4. What illusion does the process abstraction create?

The illusion that process abstraction creates is making it seem as though an operating system has the ability to handle multiple programs at once and compute a variety of things simultaneously, when in reality the system uses interrupts, virtual memory distribution, and coordinated hardware utilization to run a bunch of processes in series with limited simultaneous execution. 


5. What is the kernel?

The kernel is the part of the operating system responsible for core capabilities like creating threads.

6. What is a daemon?

A daemon is another name for processes that run in the background and provide operating system services.
