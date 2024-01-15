#include "networking.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int err1(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

static void sighandler(int signo){
    if (signo == SIGINT){
        printf("You have quit the game :( \n");
        exit(1);
    }
}


struct player* newStruct(char name[35], int score){
  struct player* player = malloc(sizeof(struct player));
  strcpy(player->name,name);
  player->score = score;
  return player;
}

void display(struct player *player){
  printf("%s, %d\n" , player -> name, player -> score);
}

void clientLogicMultiple(struct player* c, char* ip){
  //display(c);
  fd_set read_fds;
  char input[BUFFER_SIZE];

  int server_socket = client_tcp_handshake(ip);
  int loop = 0;

  printf("Ask a Question: \n");

  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket, &read_fds);

    //if(loop !=  0) canRun(server_socket, run);
    // printf("Ask a Question: \n");
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    // write(server_socket, c, sizeof(struct player));

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\r\n")] = 0;
      //printf("%s\n",input);
    //  printf("got user question\n");
      strcpy(c->question, input);
      int stuff = write(server_socket, c, sizeof(struct player));
      display(c);
      if(stuff < 0){
        err(stuff, "try to write to server");
      }
      //printf("sent to server\n");
    }


    if (FD_ISSET(server_socket, &read_fds)) {
      //printf("getting response from server\n");
      int bytes = read(server_socket, input, sizeof(input));
      if(bytes<0) err(bytes,"reading from server");
      if(bytes == 0){
        printf("0 bytes read\n");
        close(server_socket);
        server_socket = 0;
        printf("SERVER DISCONNECTED\n");
      }
      if(bytes > 0){
        if(strcasecmp(input, "yes") == 0){
            c -> score ++;
          printf("score updated\n");
        }
        printf("Current Score: %d\n", c-> score);
        printf("Answer Received (from server): %s\n", input);
        printf("Ask a Question: \n");
      }
   }

  }
}

void printTranscript(char* file) {
  char buff[BUFFER_SIZE*2]; // just in case (2000 bytes)
  int t_file;

  t_file = open(file, O_RDONLY, 0);
  if (t_file == -1) perror("reading file error\n");

  int bytes;
  bytes = read(t_file, buff, BUFFER_SIZE*2);
  // printf("bytes: %d\n", bytes);
  if(bytes == -1) {perror("reading bytes error");}//all non 0 are true

  printf("%s\n",buff);

  close(t_file);
  // }
} 


void questionsLogic(int server_socket, struct player* current){
  char buff[BUFFER_SIZE];
  int questions = 20;
  int winBoolean = 0;
  int t_file;
  sprintf(buff, "transcript_%s.txt", current->name);
  remove(buff); // remove file if already exists
  t_file = open(buff, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");

  while(1){
    printf("%d Questions left. Ask your next question:\n", questions);
    signal(SIGINT, sighandler);
    // write QUESTION 1,2, ... to transcription file
    sprintf(buff, "QUESTION %d: ", 20 - questions); // formats the string and puts it into buff
    char* p = buff;
    write(t_file, p, strlen(p));

    // writing stdin to server
    fgets(buff,sizeof(buff),stdin);
    write(server_socket, buff, sizeof(buff)); // writing question to 
    questions --;

    // writing the stdin question to transcription file
    char* question = buff;
    write(t_file, question, strlen(question));

    // read answer from server
    printf("server typing...\n");
    read(server_socket, buff, sizeof(buff));

    // write answer into transcription file
    char *r = buff;
    write(t_file, "ANSWER: ", strlen("ANSWER: "));
    write(t_file, r, strlen(r)); // put into file
    write(t_file, "\n\n", strlen("\n\n")); // formatting
    
    // checking if won
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
  
   // break becasue of win
  if(winBoolean){
    printf("you guessed the mystery word!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", current->name);
    printf("CONGRATS! Here is a transcript of the game (%s):\n", filename);
    printf("-----------------------------------------\n");
    printTranscript(filename);
    printf("-----------------------------------------\n");
  }
   // break because no more questions
  else{
    printf("Sorry!! You've reached the maximum questions!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", current->name);
    printf("Next Time! Here is a transcript of the game (%s):\n", filename);
    printf("-----------------------------------------\n");
    printTranscript(filename);
    printf("-----------------------------------------\n");
  }
}






int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("Connected Server at IP: %s\n\n", IP);


  // receiving the game mode from server
  int buffer[BUFFER_SIZE];
  printf("AIODUHIOAUSDOIASHIDAOS\n");
  read(server_socket, buffer, sizeof(buffer)); // reading mode
  printf("I WANNA KISmS\n");
  close(server_socket);
  int modeBoolean20Game = 0; // default to 2 minutes
  if(*buffer == 1){
    modeBoolean20Game = 1; // set to 20 questions
  }


  // setup name and score

  printf("mode boolean: %d\n", modeBoolean20Game);



  if(modeBoolean20Game){
    char name[35];
    int score = 0;
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\r\n")] = 0; // remove end character
    struct player* c = newStruct(name,score);
    int clientNum = 1; // for numbering questions in transcript


    printf("20 Questions Mode!\nGame Started!\n\n");
    int server_socket = client_tcp_handshake(IP);
    questionsLogic(server_socket,c);

  }
  else{

    char name[35];
    int score = 0;
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\r\n")] = 0; // remove end character
    struct player* c = newStruct(name,score);
    int clientNum = 1; // for numbering questions in transcript


    printf("2 Minutes Mode!\n");
    name[strlen(name)-1] = 0;
    // struct player* c = newStruct(name,score);

    clientLogicMultiple(c, IP);
  }
  
  

}
