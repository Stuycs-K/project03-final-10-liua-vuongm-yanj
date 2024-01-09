#include "networking.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void clientLogic(int server_socket, int num){
  char userInput[100];
  char response[100];
  int t_file;

  int pid = getpid();
  printf("client pid: %d\n", pid); // TESTING 

  char b[BUFFER_SIZE];
  sprintf(b, "transcript_%d.txt", pid);

  t_file = open(b, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");

  printf("Ask a Question: ");
  // fflush(stdin);
  // fflush(stdout);
  fgets(userInput, sizeof(userInput), stdin);

  char* question = userInput;
  char buff[100];
  sprintf(buff, "QUESTION %d: ", num);
  char* p = buff;
  write(t_file, p, strlen(p));
  write(t_file, question, strlen(question)); // put into file?
  // printf("written: %s\n", question);
  
  write(server_socket,userInput,strlen(userInput));
  //send(server_socket,userInput, sizeof(userInput),0);


  read(server_socket, response, sizeof(response)); //read modified
  printf("Answer Received (from server): %s\n", response);

  char* r = response;
  write(t_file, "ANSWER: ", strlen("ANSWER: "));
  write(t_file, r, strlen(r)); // put into file?
  write(t_file, "\n", strlen("\n")); // formatting


  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("Connected to IP: %s\n", IP);

  int clientNum = 1;
  while(1){
    int server_socket = client_tcp_handshake(IP);
    // printf("client connected.\n");
    clientLogic(server_socket, clientNum);
    clientNum++;
  }
}
