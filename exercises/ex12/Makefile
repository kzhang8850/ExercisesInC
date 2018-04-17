all: counter array_counter counter_mutex
counter: counter.c
	gcc -Wall -o counter counter.c -lpthread
array_counter: counter_array.c
	gcc -Wall -o counter_array counter_array.c -lpthread
counter_mutex: counter_mutex.c mutex.c mutex.h
	gcc -Wall -o counter_mutex counter_mutex.c mutex.c -lpthread
