/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

Edited by Kevin Zhang

Completed find_track_regex function which searches through list of tracks using regex rather than just simple string matching

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

/*
helper function that uses regex to check if a pattern and a given track match

track: individual track string to be analyzed
pattern: regex pattern to be used for matching
*/
int check_track_regex(char *track, char *pattern){
    regex_t re;

    // first compile the regex pattern
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        puts("Something went wrong with regcomp."); //regcomp failure
        exit(1);

    }

    // then match using the regex 
    int status = regexec(&re, track, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        if (status == REG_ENOSYS){
            puts("Function not supported.");   /* report error */
            exit(1);
        }
        return 0;      // else say no match
    }
    return 1;
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
/*
Completed by Kevin Zhang
Uses regex expression matching on strings to find tracks

char pattern[]: the pattern to be used for matching with string in the track list
*/
void find_track_regex(char pattern[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if(check_track_regex(tracks[i], pattern)){
            printf("Track %i: '%s'\n", i, tracks[i]);
        }

    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
