#include "server.h"
#include "networking.h"
// #include "client.h"
#include <errno.h>

struct player** leaderboard;

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
        free(temp);
      }
    }
  }
}

int serverLogicMultiple(){

  int sockets[MAX_CLIENT];
  for (int i = 0; i < MAX_CLIENT; i++) {
    sockets[i] = 0; //0 means unopened sockets
  }

  fd_set read_fds;
  int listen_socket, client_socket, current;

  current = 0;
  //assume this functuion correcly sets up a listening socket
  printf(White "Waiting for a client to connect...\n");
  listen_socket = server_setup();

  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  char input[BUFFER_SIZE];


  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  FD_SET(listen_socket, &read_fds);

  leaderboard = newStructL(); //creating leaderboard

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
       }
     }

    int v = select(current + 1, &read_fds, NULL, NULL, NULL);
    if(v<0){
      err(v, "select error");
    }

    //if socket, accept the connection
    //assume this function works correctly
    if (FD_ISSET(listen_socket, &read_fds)) {
      client_socket = server_tcp_handshake(listen_socket);
      printf(Green "A Client connected!\n\n");
      if(client_socket <= 0){
        err(client_socket, "error accepting client");
      }
      for (int i = 0; i < MAX_CLIENT; i++) {
        if (sockets[i] == 0) { // last open socket
          sockets[i] = client_socket; // store socket in first unopen socket
          printf("storing client into socket\n");
          break;
        }
      }
    }

    for (int i = 0; i < MAX_CLIENT; i++) {
      //printf("%d", sockets[i]);
      if (FD_ISSET(sockets[i], &read_fds)) {
        printf(White "Reading from Client %d\n", i);
        struct player* now = malloc(sizeof(struct player));

        int p = read(sockets[i], now, sizeof(struct player));

        if (p > 0) {
          leaderboard[i] = now;
          printf(White"Question Recieved (from client): %s \n", now->question);
          printf(Blue "answer: (yes/no/ans)\n");
          fgets(input, sizeof(input), stdin);
          input[strcspn(input, "\r\n")] = 0;
          write(sockets[i], input, sizeof(input));
          if(strcasecmp(input, "yes") == 0){
              leaderboard[i] -> score ++;
          }

          sort(leaderboard,5);
          displayL(leaderboard);
          if(strcasecmp(input, "ans") == 0){
            exit(1);
          }

          free(now);
        }
        else if(p == 0){
          close(sockets[i]);
          sockets[i] = 0;
          printf("closed");
          free(now);
        }
        else{
          perror("read error");
          free(now);
        }
      }
    }

  }

  //close(client_socket);
  return 0;
}

void questionsLogic(){
  // ----- jiayus
  // fd_set read_fds;
  // int listen_socket, client_socket, current;
  // current = 0;
  // //assume this functuion correcly sets up a listening socket

  printf(White "Waiting for client to connect...\n");
  int listen_socket = server_setup();
  int client_socket = server_tcp_handshake(listen_socket);
  printf(Green "Client connected!\n\n");

  char userInput[100];
  printf(Blue "Set your word: \n");
  printf(Clear ">> ");
  fgets(userInput, sizeof(userInput), stdin);

  char buff[BUFFER_SIZE];
  int winBoolean = 0;
  while(1){
    printf(Black "client typing....\n\n");
    int bytes_read = read(client_socket, buff, sizeof(buff));
    // detect if client is still writing stuff
    if(bytes_read){
      printf(Blue "Question: \n");
      printf(Clear ">> %s",buff);
      printf(Blue "answer: (yes/no/ans)\n");
      printf(Clear ">> ");
      fgets(buff, sizeof(buff),stdin);
      write(client_socket, buff,sizeof(buff));
      int result = strcmp(buff,"ans");
      if(result == 10){
        winBoolean = 1;
        break;
      }
    }
    else{ // if no bytes are read
      break;
    }
  }
  if(winBoolean){
    printf(Green "client guessed word!\n");
  }
  else{
    printf(Red "client lost!\n");
  }
}


int main(int argc, char *argv[] ) {

  if(strcmp(argv[1],"1") == 0){
    // code for 20 questions
    // setting the word
    printf(Magenta "20 Questions (S) Mode!\n" Clear);
    questionsLogic();
  }
  if(strcmp(argv[1],"2") == 0){
    // code for 2 minutes
    printf(Magenta "20 Questions (M)!\n" Clear);
    serverLogicMultiple();
  }

  free(leaderboard);

}
