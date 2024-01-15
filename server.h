#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include "client.h"
#ifndef SERVER_H
#define SERVER_H
#define MAX_CLIENT 5
struct player* newStruct(char name[35], int score);
struct player {char name[35]; char question[1024]; int score;};
struct player** newStructL();
int err1();
//void sendRun(int client_socket, char* input);
void subserver_logic(int client_socket);
void displayP(struct player *player);
void sort(struct player** leaderboard, int numPlayer);
void displayL(struct player** leaderboard);
#endif
