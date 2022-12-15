#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <linux/in.h>
#include <unistd.h>

#define FNAME file1
#define PORT 8010
#define BUFSIZE 128
#define LISTENQ 5

typedef struct
{
	int sock;
	struct sockaddr address;
	int addr_len;
} connection_t;

