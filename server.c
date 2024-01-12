#include "networking.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void rot13(char *input){
  for(int i = 0;i < strlen(input);i++){
    if(input[i]- 13 < 'a'){
      input[i] +=13;
    }
    else{
      input[i]-=13;
    }
  }
}

void subserver_logic(int client_socket){
  char input[BUFFER_SIZE];
  read(client_socket, input, sizeof(input)); //read from client
  printf("Question Recieved (from client): %s \n", input);
  
  printf("Answer with yes/no \n");
  fgets(input, sizeof(input), stdin);


//send(client_socket, input, sizeof(input),0);
write(client_socket, input, sizeof(input));
//close(client_socket);
printf("Message sent (to client): %s\n", input);
}

static void sighandler(int signo) {
  if (signo == SIGTSTP) {
    printf("TEST + exiting\n");
    // improve communicastion between server and clinet (send over name + PID)
    // so server knows which client wins
    exit(0);
  }
}


int main(int argc, char *argv[] ) {
  signal(SIGTSTP, sighandler);

  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  int listen_socket = server_setup();
  //int num = 0;
  fd_set read_fds;

  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket,&read_fds);

    select(listen_socket+1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(listen_socket, &read_fds)) {
      int client_socket = server_tcp_handshake(listen_socket);
      subserver_logic(client_socket);

      close(client_socket);
    }
  }
}