#include "networking.h"

int strCompare(char *s1, char *s2){
    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    int smallerSize = 0;

    if(s1Size>s2Size){
        smallerSize = s2Size;
    }
    else{
        smallerSize = s1Size;
    }

    for (int i =0; i < smallerSize; i++){
        if(s1[i] > s2[i]){
            return 1;
        }
        else if (s2[i] > s1[i]){
            return -1;
        }

    }
    if(s1Size == s2Size){
            return 0;
        }
        if(s1Size > s2Size){
            return 1;
        }
        return -1;

}

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

int main(int argc, char *argv[] ) {
  
  char mode[100];
  char str[] = "1"; 
  printf("Enter 1 for 20 Questions (one player) or 2 for 2 minutes (multi player)\n");
  fgets(mode, sizeof(mode), stdin);
  int result = strcmp(mode,str);

  if(result == 10){
    printf("20 Questions Mode!\n");
  }
  else{
    printf("2 Minutes Mode!\n");
  }

  printf("Received: %d\n", result);

  char userInput[100];
  printf("Set your word: ");
  fgets(userInput, sizeof(userInput), stdin);

  int listen_socket = server_setup();
  //int num = 0;
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
