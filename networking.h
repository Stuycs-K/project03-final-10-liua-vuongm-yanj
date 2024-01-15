#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define MINUTES 2
#define SECONDS_PER_MINUTE 60
#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);


#define Black "\033[30m"
#define Red "\033[31m"
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Blue "\033[34m"
#define Magenta "\033[35m"
#define Cyan "\033[36m"
#define White "\033[37m"
#define Clear "\033[0m"
#define Gray "\033[47m"



#endif
