#include "networking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void clientLogic(int server_socket){
  char userInput[100];
  int t_file;

  t_file = open("transcript.txt", O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("what");
  printf("open(./transcript.txt) : %d\n", t_file);

  printf("Ask a Question: ");
  // fflush(stdin);
  // fflush(stdout);
  fgets(userInput, sizeof(userInput), stdin);

  char* question = userInput;
  write(t_file, "QUESTION: ", strlen("QUESTION: "));
  write(t_file, question, strlen(question)); // put into file?
  // printf("written: %s\n", question);
  
  write(server_socket,userInput,strlen(userInput));
  //send(server_socket,userInput, sizeof(userInput),0);


  read(server_socket, userInput, sizeof(userInput)); //read modified
  printf("Answer Received (from server): %s\n", userInput);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("Connected to IP: %s\n", IP);
  while(1){
    int server_socket = client_tcp_handshake(IP);
    // printf("client connected.\n");
    clientLogic(server_socket);
  }
}
