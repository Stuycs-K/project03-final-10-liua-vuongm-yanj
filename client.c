#include "networking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void clientLogic(int server_socket){
  char userInput[100];
  printf("Input: ");
  // fflush(stdin);
  // fflush(stdout);
  fgets(userInput, sizeof(userInput), stdin);
  write(server_socket,userInput,sizeof(userInput));
  //send(server_socket,userInput, sizeof(userInput),0);


  read(server_socket, userInput, sizeof(userInput)); //read modified
  printf("Modifed Input: %s\n", userInput);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
while(1){
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
  sleep(1);
}
}
