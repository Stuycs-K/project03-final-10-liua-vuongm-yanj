#include "networking.h"

void subserver_logic(int client_socket){
  char input[BUFFER_SIZE];
  read(client_socket, input, sizeof(input)); //read from client
  printf("Message Recieved (from client): %s \n", input);

  //rot13
  for(int i = 0;i < strlen(input);i++){
    if(input[i]- 13 < 'a'){
      input[i] +=13;
    }
    else{
      input[i]-=13;
    }
  }

//send(client_socket, input, sizeof(input),0);
write(client_socket, input, sizeof(input));
//close(client_socket);
printf("Message sent (to client): %s\n", input);
}

int main(int argc, char *argv[] ) {
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
