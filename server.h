#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <fcntl.h>
#include <asl.h>
#include <unistd.h>
#include <syslog.h>

#define UNIX_PATH_MAX 108

int connection_handler(int connection_fd);
int create_server(int domain, int type, int protocol);


