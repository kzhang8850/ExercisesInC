## Homework 8

### C Exercises

Modify the link below so it points to the `ex08` directory in your
student repository.

[Here is a link to the ex08 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex08)

### Think OS Chapter 8 reading questions

**Multitasking**

1) What is the kernel's most basic task?

The kernel's most basic task is to handle interrupts, which is defined as an event that stops the normal instruction cycle and causes the flow of execution to jump to a special section of code called an "interrupt handler". It is involved in implementing multitasking for the operating system.

2) When an interrupt occurs, what part of the hardware state is saved by hardware?

When an interrupt occurs, the hardware saves the program counter in a special register before jumping to an interrupt handler, as the program counter is required so the kernel can know where to resume once the interrupt is taken care of.

3) What is the difference between an interrupt and a context switch?

The two terms are related, but with subtle differences. The main difference is in the amount of context that is required to be saved. In an interrupt, the interrupt handler still performs some "context switching", but generally not the entire hardware state, only saving, clearing, and loading registers that it plans to use. This keeps interrupt handlers fast because there's a lot less computational overhead. But context switching in this instance, where the kernel switches to a new process, is a more complete "context switch". The kernel in general doesn't know what registers a process needs, so it saves all of them, and when context switching, all data in the MMU might have to be cleared and new data for the new process might have to be loaded into the cache. This creates a larger computational overhead that makes a full context switch comparatively slower than that of a generic interrupt.

4) Give an example of an event that might cause a process to move from the blocked to the ready state.

An example might be when an operation like a disk request completes, so an interrupt will occur and the interrupt handler will figure out which process was waiting for the data and then switch that process's state from blocked to ready.

5) Why might a scheduler want to give higher priority to an I/O bound process?

This is most likely because an I/O bound process is restricted mainly by the inputs and outputs, such as reading data from the network or from the disk. That is, I/O event itself is far slower in occurring than the processing CPU time it takes to read or act on that data once it's retrieved. So it makes more sense to act on any I/O processes immediately and then go do other things while the next I/O takes "forever" to occur. This is because since the I/O request will take more time, it's best to get it started as soon as possible, and since the processing time is comparatively short, it's best to make a long-running process wait for a short one than the other way around. Thus in terms of priority, I/O bound processes are higher on the list, because the time it takes to complete them vs the rate at which they occur on the operating system skew them heavily in favor of being completed first.

6) When I make French toast, I usually make a batch of 12 slices.  But my griddle only has room for 8 slices.
Each piece of toast has to cook for 5 minutes on each side.  How can I schedule 12 slices onto 8 "cores"
to minimize the elapsed time to cook all 12 slices?  (Note: this question is not hypothetical;
this is really how I make French toast.)

To minimize the time to cook all 12 slices, you essentially want to distribute your cooking for the 24 sides such that you utilize the maximum amount of room on the griddle at any given time. In other words, first start cooking one side of 8 slices on the griddle, which will take 5 minutes. Then flip half of the slices you just cooked, and take off the other half and replace them with the 4 completely uncooked ones. Second, start cooking again, which will finish 4 of the slices, taking another 5 minutes. Then flip the 4 slices that were cooking but only finished on one side, and put the original 4 you cooked one side in the first batch back on, but flipped. Third, start cooking again, and this will finish the remaining 8 slices for both sides, which will another 5 minutes.

So in total, the least amount of time needed to cook 12 slices of French toast 15 minutes, using the method described above.
