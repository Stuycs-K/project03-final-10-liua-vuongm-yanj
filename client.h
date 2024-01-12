#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "networking.h"
#ifndef CLIENT_H
#define CLIENT_H
int err1();
struct player* newStruct(char name[35], int score);
void clientLogic(int server_socket, struct player* current);
struct player { char name[35]; int score;};
void display(struct player *player);
#endif
