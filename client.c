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

  char b[BUFFER_SIZE];
  sprintf(b, "transcript_%s.txt", current->name);

  t_file = open(b, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");

  int temp =0;
  printf("Ask a Question: ");
  fgets(userInput, sizeof(userInput), stdin);

  char buff[100];
  sprintf(buff, "QUESTION %d: ", num); // formats the string and puts it into buff
  char* p = buff;
  write(t_file, p, strlen(p));

  char* question = userInput;
  write(t_file, question, strlen(question)); // put into file

  write(server_socket,userInput,sizeof(userInput));


  read(server_socket, response, sizeof(response)); //read modified

  response[strcspn(response, "\r\n")] = 0; //remove empty space

  printf("Answer Received (from server): %s\n", response);
  if(strcasecmp(response, "yes") == 0){
      current -> score ++;
  }

  char* r = response;
  write(t_file, "ANSWER: ", strlen("ANSWER: "));
  write(t_file, r, strlen(r)); // put into file
  write(t_file, "\n\n", strlen("\n\n")); // formatting

  printf("Current Score: %d\n", current-> score);
  close(server_socket);
}


void questionsLogic(int server_socket){
  char buff[BUFFER_SIZE];
  int questions = 20;
  int winBoolean = 0;
  while(1){
    printf("%d Questions left. Ask your next question:\n", questions);
    fgets(buff,sizeof(buff),stdin);
    write(server_socket, buff, sizeof(buff)); // writing question
    questions --;

    printf("server typing...\n");
    read(server_socket, buff, sizeof(buff)); // reading answer
    
    int result = strcmp(buff,"ans"); // checking if received win
    if(result == 10){ // server said we guessed the answer!
      winBoolean = 1;
      break;
    }
    printf("answer received: %s\n", buff);
    if(questions == 0){
      break;
    }
  }
  if(winBoolean){ // break becasue of win
    printf("answer guessed!\n");
  }
  else{ // break because no more questions
    printf("You've reached the maximum questions!\n");
  }
}



int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("Connected Server at IP: %s\n\n", IP);

  // setup name and score
  char name[35];
  int score = 0;
  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\r\n")] = 0; // remove end character
  struct player* c = newStruct(name,score);

  int clientNum = 1; // for numbering questions in transcript


  // receiving the game mode from server
  int buffer[BUFFER_SIZE];
  read(server_socket, buffer,sizeof(buffer)); // reading mode
  int modeBoolean20Game = 0; // default to 2 minutes
  if(*buffer == 1){
    modeBoolean20Game = 1; // set to 20 questions
  }



  if(modeBoolean20Game){
    printf("20 Questions Mode!\nGame Started!\n\n");
    questionsLogic(server_socket);

  }
  else{
    printf("2 Minutes Mode!\n");
    while(1){
    int server_socket = client_tcp_handshake(IP);
    clientLogic(server_socket, c, clientNum);
    clientNum++;
    }
  }
  
}
