#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef CLIENT_H
#define CLIENT_H
struct player* newStruct(char name[35], int score);
void clientLogic(int server_socket, struct player* current, int num);
struct player { char name[35]; int score;};
void display(struct player *player);
#endif
