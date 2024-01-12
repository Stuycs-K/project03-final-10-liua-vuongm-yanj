#include "server.h"
#include "networking.h"
#include <errno.h>
int err1(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

void displayP(struct player *player){
  printf("%s,%d\n" , player -> name, player -> score);
}

void displayL(struct leaderboard *leaderboard){
  displayP(leaderboard -> p1);
  displayP(leaderboard -> p2);
  displayP(leaderboard -> p3);
  displayP(leaderboard -> p4);
  displayP(leaderboard -> p5);
}

// void subserver_logic(int client_socket){
//   char input[BUFFER_SIZE];
//   read(client_socket, input, sizeof(input)); //read from client
//   printf("Question Recieved (from client): %s \n", input);
//
//   printf("Answer with yes/no \n");
//   fgets(input, sizeof(input), stdin);
//
//
// //send(client_socket, input, sizeof(input),0);
// write(client_socket, input, sizeof(input));
// //close(client_socket);
// printf("Message sent (to client): %s\n", input);
// }

int main(int argc, char *argv[] ) {
  int sockets[MAX_CLIENT];
  for (int i = 0; i < MAX_CLIENT; i++) {
    sockets[i] = 0; //0 means unopened sockets
  }

  fd_set read_fds;
  int listen_socket, client_socket, current;

  //assume this functuion correcly sets up a listening socket
  listen_socket = server_setup();



  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  char input[BUFFER_SIZE];
  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket, &read_fds);


    current = listen_socket; // file descriptor of current client
     for (int i = 0; i < MAX_CLIENT; i++) {
       if (sockets[i] != 0){
         FD_SET(sockets[i], &read_fds);
         printf("socket %d open\n", i);
       }
       if (sockets[i] > current){
         current = sockets[i];
       }
       //makes sure that it is the biggest open because the you have to select from the biggest one
     }

    printf("waiting until client found\n");
    select(current + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      printf("reading from stdin\n");
      fgets(input, sizeof(input), stdin);
      for (int i = 0; i < MAX_CLIENT; i++) {
        if (sockets[i] != 0) {
          if(write(sockets[i], input, sizeof(input))) err1();
          printf("Message sent (to client %d): %s\n", i, input);
        }
      }
    }

    //if socket, accept the connection
    //assume this function works correctly
    if (FD_ISSET(listen_socket, &read_fds)) {
      client_socket = server_tcp_handshake(listen_socket);
      if(client_socket <= 0){
        err1();
      }
      for (int i = 0; i < MAX_CLIENT; i++) {
        if (sockets[i] == current) { // last open socket
          sockets[i+1] = client_socket; // store socket in first unopen socket
        }
      }
    }

    for (int i = 0; i < MAX_CLIENT; i++) {
      if (FD_ISSET(sockets[i], &read_fds)) {
        printf("reading from socket %d\n", i);
        int bytes = read(sockets[i], input, sizeof(input));
        if (bytes > 0) {
          printf("Question Recieved (from client): %s \n", input);
          printf("Answer with yes/no \n");
        }
      }
    }


   //close(client_socket);
  }
  return 0;
}
