## Homework 1

### C Exercises

[Here is a link to the ex01 directory in my repository](https://github.com/kzhang8850/ExercisesInC/tree/master/exercises/ex01)

### Think OS Chapter 1 reading questions

For each of the reading questions below, write answers in the form of
a clear, concise, complete sentence or two.

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.

A feature common in interpreted languages but rare in compiled languages is dynamic types. This generally means that interpreted languages declare types at runtime, whereas compiled languages declare them at compilation. It also means that for compiled languages you can tell what type a variable refers just by looking at the program, whereas the same is not true for interpreted languages.

2) Name two advantages of static typing over dynamic typing.

One advantage is that errors can be found more quickly because checks on the correct types for arguments and returns happen at compile time, which also means that errors can be found on portions that have never been run. Another advantage is that static typing saves space, as names of variables exists only during compile time, giving runtime more room.

3) Give an example of a static semantic error.

An example is an error where a function is called without the right number of arguments or the wrong type of arguments.

4) What are two reasons you might want to turn off code optimization?

One reason is that it makes debugging easier, as increasing optimization levels can bring about or hide subtle bugs, which might change the behavior of the program and cause confusion. Another reason is if you are developing new code, as leaving off as many possible confounding variables when making something you are not familiar with is a good idea. As a small tidbit, optimization seems to also increase compile time with increasingly higher tier optimization levels, so especially for rapid prototyping to make something work, faster compile times and more iterations on code would be favored over "clean" code that might not work yet.

5) When you run `gcc` with `-S`, why might the results look different on different computers?

gcc is usually configured to generate machine code for the machine you are running. So machines with different architectures from the conventional x86 assembly language type that processors like Intel, AMD, etc. use might see a different result.

6) If you spell a variable name wrong, or if you spell a function name wrong, the error messages
you get might look very different.  Why?

This is because syntax errors and function miscalls are checked in different parts of the compilation process and thus different programs that interact with the C language. Spelling a variable name wrong is a syntax error and thus is checked by the compiler. Spelling a function name wrong is considered an undefined function, and thus is checked by the linker. Different programs that check different things in the various steps of the compilation process have different formats, jargon, and wording.

7) What is a segmentation fault?

A segmentation fault is trying to read or write an incorrect location in memory.
