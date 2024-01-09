#include "networking.h"
#include "semaphore.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void clientLogic(int server_socket, int semd){
  char userInput[100];
  printf("Ask a Question: ");
  fgets(userInput, sizeof(userInput), stdin);
  write(server_socket,userInput,sizeof(userInput));
  read(server_socket, userInput, sizeof(userInput));
  printf("Answer Received (from server): %s\n", userInput);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  int semd = semSetup(1);
  if(argc>1){
    IP=argv[1];
  }
  printf("Connected to IP: %s\n", IP);
  while(1){
    int server_socket = client_tcp_handshake(IP);
    printf("client connected.\n");
    clientLogic(server_socket, semd);
  }
}
