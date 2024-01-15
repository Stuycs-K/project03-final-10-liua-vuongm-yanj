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
int serverLogicMultiple(){
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

void questionsLogic(){
  // ----- jiayus
  // fd_set read_fds;
  // int listen_socket, client_socket, current;
  // current = 0;
  // //assume this functuion correcly sets up a listening socket

  // listen_socket = server_setup();
  int listen_socket = server_setup();
  int client_socket = server_tcp_handshake(listen_socket);
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

  // setting the game mode
  char modeStdIn[100];
  int modeBoolean20Game = 0; // default is 2 minutes, boolean is false
  printf(White "Enter 1 for 20 Questions (one player) or 2 for 2 minutes (multi player)\n>> ");
  fgets(modeStdIn, sizeof(modeStdIn), stdin);
  int result = strcmp(modeStdIn,"1"); // not sure why it returns 10 if equal
  if(result == 10){ // if user input is 1
    modeBoolean20Game = 1; // boolean set to true
    printf(Magenta "20 Questions Mode!\n" Clear);
  }
  else{
    printf( Magenta "2 Minutes Mode!\n");
  }

  
  // communicate game mode to client

  printf(Black "Waiting for client to connect...\n");  
  int listen_socket = server_setup();
  int client_socket = server_tcp_handshake(listen_socket);
  printf(Green "Client connected!\n\n");
  write(client_socket, &modeBoolean20Game, sizeof(modeBoolean20Game));
  close(listen_socket);
  close(client_socket);

  if(modeBoolean20Game){
    // code for 20 questions
    // setting the word
    
    questionsLogic();

  }
  else{
    // code for 2 minutes
    serverLogicMultiple();
  }

}

// int main(int argc, char *argv[] ) {
//   serverLogicMultiple();
// }
