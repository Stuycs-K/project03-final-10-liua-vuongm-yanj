#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "networking.h"
#ifndef CLIENT_H
#define CLIENT_H
int err1();
int canRun(int server_socket, int run);
struct player* newStruct(char name[35], int score);
void clientLogic(int server_socket, struct player* current);
struct player { char name[35]; char question[1024]; int score;};
void display(struct player *player);
void clientLogicMultiple(struct player* c, char* ip);
void questionsLogic(struct player* current, char* ip);
#endif
