#include "server.h"
#include "networking.h"
// #include "client.h"
#include <errno.h>
int err1(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

void displayP(struct player *player){
  printf("%s, %d\n" , player -> name, player -> score);
}

struct player* newStruct(char name[35], int score){
  struct player* player = malloc(sizeof(struct player));
  strcpy(player->name,name);
  player->score = score;
  return player;
}

struct player** newStructL(){
  struct player** leaderboard = malloc((sizeof(struct player))*5);
  for (int i = 0; i < 5; i++) {
    leaderboard[i] = malloc(sizeof(struct player));
  }
  return leaderboard;
}

void displayL(struct player** leaderboard){
  printf("\n");
  printf("Leaderboard:\n");
  for (int i = 0; i < 5; i++) {
    printf("Client %d: ", i);
    displayP(leaderboard[i]);
  }
    printf("\n");
}

void sort(struct player** leaderboard, int numPlayer){
  for(int i = 0; i<numPlayer; i++){
    for(int j = i+1; j<numPlayer; j++){
      if(leaderboard[i]-> score < leaderboard[j]-> score){
        //struct player* temp = newStruct(name,score);
        struct player* temp = newStruct(leaderboard[i]-> name, leaderboard[i]-> score);
        leaderboard[i] = leaderboard[j];
        leaderboard[j] = temp;
      }
    }
  }
}


// void sendRun(int client_socket, char* input){
//  //0 = run 1 = no
//   write(client_socket, input, sizeof(input));
// }

int main(int argc, char *argv[] ) {
  int sockets[MAX_CLIENT];
  for (int i = 0; i < MAX_CLIENT; i++) {
    sockets[i] = 0; //0 means unopened sockets
  }

  fd_set read_fds;
  int listen_socket, client_socket, current;
  current = 0;
  //assume this functuion correcly sets up a listening socket

  listen_socket = server_setup();

  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  char input[BUFFER_SIZE];
  struct player* now = malloc(sizeof(struct player));

  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  FD_SET(listen_socket, &read_fds);

  struct player** leaderboard = newStructL(); //creating leaderboard

  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket, &read_fds);

    current = listen_socket; // file descriptor of current client
     for (int i = 0; i < MAX_CLIENT; i++) {
       if (sockets[i] > 0){
         FD_SET(sockets[i], &read_fds);
         //printf("socket %d open\n", i);
       }
       if (sockets[i] > current){
         current = sockets[i];
         //printf("setting current to open socket\n");
       }
       // else{
       //   printf("something is wrong\n");
       // }
       //makes sure that it is the biggest open because the you have to select from the biggest one
     }




    int v = select(current + 1, &read_fds, NULL, NULL, NULL);
    if(v<0){
      err(v, "select error");
    }

    //if socket, accept the connection
    //assume this function works correctly
    if (FD_ISSET(listen_socket, &read_fds)) {
      client_socket = server_tcp_handshake(listen_socket);
      if(client_socket <= 0){
        err(client_socket, "error accepting client");
      }
      for (int i = 0; i < MAX_CLIENT; i++) {
        if (sockets[i] == 0) { // last open socket
          sockets[i] = client_socket; // store socket in first unopen socket
          //leaderboard[i] = client_socket;
          printf("storing client into socket\n");
          break;
        }
      }
    }

    for (int i = 0; i < MAX_CLIENT; i++) {
      //printf("%d", sockets[i]);
      if (FD_ISSET(sockets[i], &read_fds)) {
        printf("reading from socket %d\n", i);
        int p = read(sockets[i], now, sizeof(struct player));
        //printf("%s\n", leaderboard[i] -> name);
        if (p > 0) {
          leaderboard[i] = now;
          displayL(leaderboard);
          printf("Question Recieved (from client): %s \n", now->question);
          printf("Answer with yes/no \n");
          fgets(input, sizeof(input), stdin);
          input[strcspn(input, "\r\n")] = 0;
          write(sockets[i], input, sizeof(input));
          if(strcasecmp(input, "yes") == 0){
              leaderboard[i] -> score ++;
          }
          displayL(leaderboard);
        }
        else if(p == 0){
          close(sockets[i]);
          sockets[i] = 0;
          printf("closed");
        }
        else{
          perror("read error");
        }
      }
    }

  }

  //close(client_socket);
  return 0;
}
