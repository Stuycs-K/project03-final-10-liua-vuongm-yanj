#include "networking.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int err1(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
struct player* newStruct(char name[35], int score){
  struct player* player = malloc(sizeof(struct player));
  strcpy(player->name,name);
  player->score = score;
  return player;
}

void display(struct player *player){
  printf("%s,%d\n" , player -> name, player -> score);
}

// void clientLogic(int server_socket, struct player* current){
//   char userInput[100];
//   int temp =0;
//   printf("Ask a Question: ");
//   // fflush(stdin);
//   // fflush(stdout);
//   fgets(userInput, sizeof(userInput), stdin);
//   write(server_socket,userInput,sizeof(userInput));
//   //send(server_socket,userInput, sizeof(userInput),0);
//
//
//   read(server_socket, userInput, sizeof(userInput)); //read modified
//
//   userInput[strcspn(userInput, "\r\n")] = 0; //remove empty space
//
//   //printf("%s\n",userInput);
//   printf("Answer Received (from server): %s\n", userInput);
//   if(strcasecmp(userInput, "yes") == 0){
//       current -> score ++;
//     //printf("hello");
//   }
//
//   printf("Current Score: %d\n", current-> score);
//   close(server_socket);
// }

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  // int run = 0; //0 run 1 not run
  // time_t start = time(NULL);
  //printf("Connected to IP: %s\n", IP);
  char name[35];
  int score = 0;
  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  struct player* c = newStruct(name,score);
  //display(c);
  fd_set read_fds;
  char input[BUFFER_SIZE];

  int server_socket = client_tcp_handshake(IP);

  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket, &read_fds);

  printf("Ask a Question: \n");
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\r\n")] = 0;
      printf("got user question\n");
      int stuff = write(server_socket,input,sizeof(input));
      err(stuff, "try to write to server");
      printf("sent to server");
      printf("Current Score: %d\n", c-> score);
    }


    if (FD_ISSET(server_socket, &read_fds)) {
      printf("getting response from server\n");
      int bytes = read(server_socket, input, sizeof(input));
      if(bytes<0) err(bytes,"reading from server");
      if(bytes == 0){
        printf("0 bytes read\n");
      }
      if(bytes > 0){
        printf("Answer Received (from server): %s\n", input);
        if(strcasecmp(input, "yes") == 0){
            c -> score ++;
          printf("score updated\n");
      }
      }
   }

    // if(run == 0){
    //   while(time(NULL) - start < (time_t) (MINUTES * SECONDS_PER_MINUTE)) {
      // int server_socket = client_tcp_handshake(IP);
      //printf("client connected.\n");
      // clientLogic(server_socket, c);
      // sleep(1);
      // printf("%ld\n", time(NULL) - start);
    // }
    // }

  }
  // close(server_socket);

}
