#include "networking.h"
#include "semaphore.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void clientLogic(int server_socket, int semd){
  char userInput[100];
  printf("Ask a Question: ");
  // fflush(stdin);
  // fflush(stdout);
  fgets(userInput, sizeof(userInput), stdin);

  // attempting to access
  printf("waiting for server to answer other user's questions\n");
  accessSemaphore(semd);
  write(server_socket,userInput,sizeof(userInput));
  printf("waiting for response!\n");
  //send(server_socket,userInput, sizeof(userInput),0);


  read(server_socket, userInput, sizeof(userInput));
  // release the semaphore once an answer is received
  releaseSemaphore(semd);
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
