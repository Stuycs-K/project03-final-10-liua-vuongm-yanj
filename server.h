#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef SERVER_H
#define SERVER_H
struct leaderboard* newStruct(int score1, int score2, int score3, int score4, int score5);
void subserver_logic(int client_socket);
void display(struct leaderboard *leaderboard);
#endif
