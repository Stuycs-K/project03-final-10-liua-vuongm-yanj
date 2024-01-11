#include "networking.h"
#include "semaphore.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct player* newStruct(char name[35], int score){
  struct player* player = malloc(sizeof(struct player));
  strcpy(player->name,name);
  player->score = score;
  return player;
}

void display(struct player *player){
  printf("%s,%d\n" , player -> name, player -> score);
}

void clientLogic(int server_socket, struct player* current){
  char userInput[100];
  int temp =0;
  printf("Ask a Question: ");
  fgets(userInput, sizeof(userInput), stdin);

  write(server_socket,userInput,sizeof(userInput));

  read(server_socket, userInput, sizeof(userInput)); //read modified

  userInput[strcspn(userInput, "\r\n")] = 0; //remove empty space

  //printf("%s\n",userInput);
  printf("Answer Received (from server): %s\n", userInput);
  if(strcasecmp(userInput, "yes") == 0){
      current -> score ++;
    //printf("hello");
  }

  printf("Current Score: %d\n", current-> score);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("Connected to IP: %s\n", IP);
  char name[35];
  int score = 0;
  printf("Enter your name:\n");

  // printf("Attemptting to access\n");
  // accessSemaphore();
  // printf("Semaphore accessed!\n");
  fgets(name, sizeof(name), stdin);
  // releaseSemaphore();
  // printf("released semaphore\n");

  struct player* c = newStruct(name,score);
  display(c);
  while(1){
    int server_socket = client_tcp_handshake(IP);
    //printf("client connected.\n");
    clientLogic(server_socket, c);
  }
}
