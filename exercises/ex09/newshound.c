/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.

Completed by Kevin Zhang

Softsys Spring 2018

spawns 5 new processes to simultaneously execute a python script
to scrape news data off the web.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>

/*
wrapper for error handling

msg: the error message
*/
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}


/*
the child code function that a newly spawned process will run
it uses execle to execute a python script that scrapes the web for news

i: the child process number, used in sleep for chronological order execution
PYTHON: the python path
SCRIPT: the script path
search_phrase: the phrase to search for in the news data,
a parameter for the python script
vars: the specific feed that this process will look for in the news
*/
void child_code(int i, const char *PYTHON, const char *SCRIPT, char * search_phrase, char *vars[]){
    sleep(i);
    int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
    if (res == -1) {
        error("Can't run script.");
    }
    exit(0);
}


/*
main function, which initializes variables, starts processes for the
number of feeds, and then checks to make sure that all processes run
without problems before exiting
*/
int main(int argc, char *argv[])
{
    // checking invokation
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }

    // variables
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];
    pid_t pid;
    int status;

    // spawning new child processes
    for (int i=0; i<num_feeds; i++) {
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        printf("Creating child %d.\n", i);
        pid = fork();

        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }
        if(!pid){
            child_code(i, PYTHON, SCRIPT, search_phrase, vars);
        }

    }

    // waiting and checking to make sure they all finish smoothly
    for (int i=0; i<num_feeds; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }


    exit(0);
}
