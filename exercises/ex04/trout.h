#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/un.h>
#include <stdarg.h>
#include <syslog.h>
#include <strings.h>

#define BUFSIZE 1500

#define ICMP_TIME_EXCEEDED 100
#define ICMP_PORT_UNREACH 100
#define ICMP_DEST_UNREACH 100
#define ICMP_EXC_TTL 100

typedef struct rec {                /* outgoing UDP data */
  u_short seq;          /* sequence number */
} Rec;

typedef struct timeval Timeval;
typedef struct sockaddr Sockaddr;

/* the following are a few definitions from Stevens' unp.h */

#define max(a,b) ((a) > (b) ? (a) : (b))


/* the following are prototypes for the Stevens utilities in util.c */



void loop_ttl();

/* variables we might want to configure */
int max_ttl;
int nprobes;

/* other global variables */

int seq;

char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];
Rec *rec;

int sendfd, recvfd;
int pipefd[2];              /* the pipe for the alarm handler */

Sockaddr *sasend;    /* socket addresses for various purposes */
Sockaddr *sarecv;
Sockaddr *salast;
Sockaddr *sabind;

socklen_t salen;                    /* length of a socket address */
int datalen;         /* length of the data in a datagram */

u_short sport;                      /* source UDP port # */
u_short dport;        /* destination port -- hopefully unused */
                                    /* 668 = the neighbor of the beast */
Timeval sendtv[1];
Timeval recvtv[1];
Timeval difftv[1];
