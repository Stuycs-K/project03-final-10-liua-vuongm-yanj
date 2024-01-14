#include "networking.h"


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

void questionsLogic(int client_socket){
  char buff[BUFFER_SIZE];
  int winBoolean = 0;
  while(1){
    printf("client typing....\n");
    int bytes_read = read(client_socket, buff, sizeof(buff));
    // detect if client is still writing stuff
    if(bytes_read){
      printf("Question from player: %s\n",buff);
      printf("Answer yes/no/ans\n");
      fgets(buff, sizeof(buff),stdin);
      write(client_socket, buff,sizeof(buff));
      int result = strcmp(buff,"ans");
      if(result == 10){
        winBoolean = 1;
        break;
      }
    }
    else{ // game is over!
      break;
    }
  }
  if(winBoolean){
    printf("client guessed word!\n");
  }
  else{
    printf("client lost!\n");
  }
}


int main(int argc, char *argv[] ) {

  // setting the game mode
  char modeStdIn[100];
  int modeBoolean20Game = 0; // default is 2 minutes, boolean is false
  printf("Enter 1 for 20 Questions (one player) or 2 for 2 minutes (multi player)\n");
  fgets(modeStdIn, sizeof(modeStdIn), stdin);
  int result = strcmp(modeStdIn,"1"); // not sure why it returns 10 if equal
  if(result == 10){ // if user input is 1
    modeBoolean20Game = 1; // boolean set to true
    printf("20 Questions Mode!\n");
  }
  else{
    printf("2 Minutes Mode!\n");
  }


  // setting the word
  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  // communicate game mode to client

  printf("Waiting for client to connect...\n");  
  int listen_socket = server_setup();
  int client_socket = server_tcp_handshake(listen_socket);
  printf("Client connected!\n\n");
  write(client_socket, &modeBoolean20Game, sizeof(modeBoolean20Game));

  if(modeBoolean20Game){
    // code for 20 questions
    questionsLogic(client_socket);

  }
  else{
    // code for 2 minutes
    int x = 0;
    while(x == 0){
    int client_socket = server_tcp_handshake(listen_socket);
    //num++;
    pid_t f = fork();
    if(f == 0){
      subserver_logic(client_socket);
      //close(client_socket);
      exit(0);
    }
    else{
      close(client_socket);
    }
    }
  }
}
