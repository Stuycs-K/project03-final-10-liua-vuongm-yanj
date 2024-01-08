#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef CLIENT_H
#define CLIENT_H
void clientLogic(int server_socket);
struct player { char name[35]; int score;};
#endif
