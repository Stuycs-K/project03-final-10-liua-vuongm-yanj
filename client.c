#include "networking.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

struct player* newStruct(char name[35], int score){
  struct player* player = malloc(sizeof(struct player));
  strcpy(player->name,name);
  player->score = score;
  return player;
}

void display(struct player *player){
  printf("%s,%d\n" , player -> name, player -> score);
}

void clientLogic(int server_socket, struct player* current, int num){
  char userInput[100];
  char response[100];
  int t_file;

  int pid = getpid();
  printf("client pid: %d\n", pid); // TESTING 

  char b[BUFFER_SIZE];
  sprintf(b, "transcript_%d.txt", pid);

  t_file = open(b, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");

  int temp =0;
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

  write(server_socket,userInput,sizeof(userInput));
  //send(server_socket,userInput, sizeof(userInput),0);


  read(server_socket, userInput, sizeof(userInput)); //read modified

  userInput[strcspn(userInput, "\r\n")] = 0; //remove empty space

  //printf("%s\n",userInput);
  printf("Answer Received (from server): %s\n", userInput);

  char* r = response;
  write(t_file, "ANSWER: ", strlen("ANSWER: "));
  write(t_file, r, strlen(r)); // put into file?
  write(t_file, "\n", strlen("\n")); // formatting


  if(strcasecmp(userInput, "yes") == 0){
      current -> score ++;
    //printf("hello");
  }

  printf("Current Score: %d\n", current-> score);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("Connected to IP: %s\n", IP);
  char name[35];
  int score = 0;
  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  struct player* c = newStruct(name,score);
  //display(c);
  int clientNum = 1;
  while(1){
    int server_socket = client_tcp_handshake(IP);
    //printf("client connected.\n");
    clientLogic(server_socket, c, clientNum);
    clientNum++;
  }
}
