util.o: util.h util.c
	gcc -Wall -c util.c

trout.o: trout.h trout.c
	gcc -Wall -c trout.c

main: util.o trout.o main.c
	gcc -Wall -g -o main  main.c util.o trout.o
