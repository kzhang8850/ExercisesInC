/*
This code is meant to demonstrate some properties of optimization in C.

Most notably, it would appear that optimization in C either removes or compresses
many of the commands in order to speed up the program. We looked at assembly
language for this script, hello.s, to show some concepts.

The first experiment was to initialize a new variable named x at value 5. Before
optimization you can see a command movl that has a 5 and %rbp, which means
moving a piece of data from the stack to a register. That corresponds to the variable
x. After optimization, that command as well as many other movl commands are
removed from the assembly language. It would appear the movements between register
 and memory are minimized, but the overall logic/arithmetic commands that define
 the functionality of this script remain.

The next experiment was to print the variable x. Before optimization, you can see
the movl command for the variable x from before, and a separate new movl command that's
something something %esi, which corresponds to the movl command and most likely
links to printing the variable. After optimization, these two commands as well as
others are combined into one, so basically the variable is kind of initialized
and printed in the same command, rather than moving it around a lot before
actually completing the desired function.

The last experiment was to add a new variable y that was assigned x+1 and then print
it. Before optimization you can see the variable x movl command, and a series of
movl commands that move the piece of data from initialization to being used by y
in its own initialization, then to another place in the register, and then another
place, finally being printed. After optimization, all of these movl commands and
more are compressed, the 5 becomes a 6, and %esi combines with the 6 into one movl
command. Before there were more than 10 movls, and after there is literally 1.

In conclusion, it would seem apparent that optimization, especially in this case,
basically minimizes the movements between the register and the memory. The most
fundamental logic and arithmetic commands that make up the functionality remain,
but optimization compresses a lot of the steps into singular commands that can
perform equivalent function but reduce the number of processes needed to get that
functionality. Thus it is in this way that optimization can speed up programs.
*/
#include <stdio.h>


int main() {
    int x = 5;
    int y = x + 1;
    printf("Hello, World! %i", y);
    return 0;
}
