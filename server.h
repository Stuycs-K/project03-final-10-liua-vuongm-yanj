#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef SERVER_H
#define SERVER_H
#define MAX_CLIENT 5
struct player {char name[35]; int score;};
struct leaderboard {struct player* p1; struct player* p2; struct player* p3; struct player* p4; struct player* p5;};
int err1();
void sendRun(int client_socket, char* input);
void subserver_logic(int client_socket);
void displayP(struct player *player);
void displayL(struct leaderboard *leaderboard);
#endif
