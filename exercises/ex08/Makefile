all: word_count ex_compile

word_count: word_count.c
	gcc -Wall `pkg-config --cflags --libs glib-2.0` word_count.c -o word_count
ex_compile: ex_compile.c
	gcc -Wall `pkg-config --cflags --libs glib-2.0` ex_compile.c -o ex_compile
