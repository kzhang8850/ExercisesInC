/*
naive implementation of tee command in Unix systems that allows user
to chain standard inputs with standard outputs and also writing to a file
at the same time.

Biggest thing that slowed me down was integration. I did a good job of testing out all the smaller pieces and making sure each individual step worked. I had some trouble when trying to link it all together. One small thing that did trip me for quite some time was pointers, as there's some weird need to use double ** make dereference char arrays, which I didn't know about. I think next time I will most likely focus more on making sure that I understand the flow of execution and how all the pieces will connect together better, that way integration will be smoother.

In terms of the professional solution over mine, their is really just far more robust and well structured. They use header files and external scripts to hold certain methods that they use in tee. They also make no assumptions and check for all possible problems. My implementation is slightly simplified, for example I assume a 80 length char array is enough for most single line inputs, which obviously is not the case in real application. Also, they do a great job of compartmentalizing everything into its own formal declaration, with even flags or errors being made as globals or macros for instance. It would seem that professional code is far more rigorous and well put together than I had imagined.

By Kevin Zhang
softsys spring 2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
sets up initial variables and some initial checks

argc: the argc from main
argv: the argv from main
ch: the variable used to go through the options with getopt
mode: the variable that holds the file writing/appending mode toggle
*/
int set_up(int *argc, char **argv[], char *ch, char **mode){

    while ((*ch = getopt(*argc, *argv, "a")) != EOF){
        switch (*ch){
            case 'a':
                *mode = "a";
                break;
        }
    }
    *argc -= optind;
    *argv += optind;

    if (*argc < 1){
        fprintf(stderr, "Not enough arguments. You must specify at least a file path\n");
        return 1;
    }

    return 0;
}


/*
main run loop, which opens a file and then takes standard and puts it in
standard output and writes it to a file

out_file: the file to be written to
line: the input buffer that will be stdout'ed and written to out_file
argv: the argv from main
mode: the variable that determines whether writing to a file will overwrite or append
*/
int run(FILE *out_file, char *line, char *argv[], char *mode){
    out_file = fopen(argv[0], mode);
    if (out_file == NULL){
        fprintf(stderr, "opening file failed.");
        return 2;
    }

    while (scanf("%79s", line) == 1){
        fprintf(stdout, "%s\n", line);
        int check = fprintf(out_file, "%s\n", line);
        if (check < 0){
            fprintf(stderr, "writing to file failed.");
            return 3;
        }
    }
    fclose(out_file);
    return 0;
}


/*
main function, which sets up initial variables and then runs a loop to put
standard input into output and then write to file

argc: the number of arguments upon calling this script
argv: the array containing all said arguments including options
*/
int main (int argc, char *argv[]){

    char line[80];
    char *mode = "w";
    char ch;
    FILE *out_file;
    int res;

    res = set_up(&argc, &argv, &ch, &mode);
    if (res > 0){
        return res;
    }
    res = run(out_file, line, argv, mode);
    if (res > 0){
        return res;
    }

    return 0;
}
