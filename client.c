#include "networking.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

char* GLOBAL_NAME;

int err1(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

void printTranscript(char* file) {
  char buff[BUFFER_SIZE*2]; // just in case (2000 bytes)
  int t_file;

  t_file = open(file, O_RDONLY, 0);
  if (t_file == -1) perror("reading file error\n");

  int bytes;
  bytes = read(t_file, buff, BUFFER_SIZE);
  // printf("bytes: %d\n", bytes);
  if(bytes == -1) {perror("reading bytes error");}//all non 0 are true

  printf("%s\n",buff);

  close(t_file);
  // }
}


static void sighandler(int signo){
  if (signo == SIGINT){
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", GLOBAL_NAME);
    printf(Red "\nYou have quit the game :( \n");
    printf(White "Here is a transcript of your game (%s):\n", filename);
    printf("-----------------------------------------\n");
    printTranscript(filename);
    printf("-----------------------------------------\n");
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
  //printf("hello");
  fd_set read_fds;
  char input[BUFFER_SIZE];
  int winBoolean = 0;
  int t_file;
  sprintf(input, "transcript_%s.txt", c->name);
  remove(input); // remove file if already exists
  t_file = open(input, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");


  int server_socket = client_tcp_handshake(ip);
  //int bug = 0;
  while(1){
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket, &read_fds);

    //if(loop !=  0) canRun(server_socket, run);
    //printf("Ask a Question: \n");
    //  if(bug!= 0) printf("Ask a Question: ");
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);
    // write(server_socket, c, sizeof(struct player));
    //bug++;
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\r\n")] = 0;
      strcpy(c->question, input);
      int stuff = write(server_socket, c, sizeof(struct player));
      if(stuff < 0){
        err(stuff, "try to write to server");
      }
      char *question = input;
      write(t_file, "QUESTION: ", strlen("QUESTION: "));
      write(t_file, question, strlen(question));
      write(t_file, "\n\n", strlen("\n\n")); // formatting
    }


    if (FD_ISSET(server_socket, &read_fds)) {
      int bytes = read(server_socket, input, sizeof(input));
      if(bytes<0) err(bytes,"reading from server");
      if(bytes == 0){
        printf("0 bytes read\n");
        close(server_socket);
        server_socket = 0;
        printf("SERVER DISCONNECTED\n");
        printf("GAME END");
        exit(1);
      }
      if(bytes > 0){
        char* r = input;
        write(t_file, "ANSWER: ", strlen("ANSWER: "));
        write(t_file, r, strlen(r)); // put into file
        write(t_file, "\n\n", strlen("\n\n")); // formatting

        if(strcasecmp(input, "yes") == 0){
            c -> score ++;
          printf("score updated\n");
        }

        if(strcasecmp(input, "ans") == 0){
          winBoolean = 1;
          break;
        }
        printf("Current Score: %d\n", c-> score);
        printf("Answer Received (from server): %s\n", input);
        printf("Ask a Question: \n");
      }
   }
  }
  if(winBoolean){
    printf(Green "You guessed the mystery word!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", c->name);
    printf(White "CONGRATS! Here is a transcript of the game (%s):\n", filename);
    printf("-----------------------------------------\n");
    printTranscript(filename);
    printf("-----------------------------------------\n");
  }
   // break because no more questions
  else{
    printf(Red "Sorry!! You've reached the maximum questions!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", c->name);
    printf( White "Next Time! Here is a transcript of the game (%s):\n", filename);
    printf(Black "-----------------------------------------\n");
    printTranscript(filename);
    printf(Black "-----------------------------------------\n");
  }
}


void questionsLogic(struct player* current, char* ip){
  int server_socket = client_tcp_handshake(ip);

  char buff[BUFFER_SIZE];
  int questions = 20;
  int winBoolean = 0;
  int t_file;
  sprintf(buff, "transcript_%s.txt", current->name);
  remove(buff); // remove file if already exists
  t_file = open(buff, O_RDWR | O_APPEND | O_CREAT, 0611);
  if (t_file == -1) perror("opening file error");

  while(1){
    printf(Yellow "%d Questions left.\n", questions);
    printf(Blue "Ask your next question:\n");
    printf(White ">> ");
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
    printf(Black "server typing...\n");
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
    printf(Blue "answer: \n");
    printf(White ">> %s\n", buff);
    if(questions == 0){
      break;
    }
  }

   // break becasue of win
  if(winBoolean){
    printf(Green "You guessed the mystery word!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", current->name);
    printf(White "CONGRATS! Here is a transcript of the game (%s):\n", filename);
    printf("-----------------------------------------\n");
    printTranscript(filename);
    printf("-----------------------------------------\n");
  }
   // break because no more questions
  else{
    printf(Red "Sorry!! You've reached the maximum questions!\n");
    char filename[BUFFER_SIZE];
    sprintf(filename, "transcript_%s.txt", current->name);
    printf( White "Next Time! Here is a transcript of the game (%s):\n", filename);
    printf(Black "-----------------------------------------\n");
    printTranscript(filename);
    printf(Black "-----------------------------------------\n");
  }
}






int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";

  if(strcmp(argv[1],"1") == 0){
    char name[35];
    int score = 0;
    printf(Blue "Enter your name: \n");
    printf(White ">> " Clear);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\r\n")] = 0; // remove end character
    struct player* c = newStruct(name,score);
    GLOBAL_NAME = c->name;
    int clientNum = 1; // for numbering questions in transcript


    printf(Magenta "20 Questions (S) Mode!\n");
    printf(Cyan "Game Started!\n\n");
    questionsLogic(c,IP);
  }
  if(strcmp(argv[1],"2") == 0){
    printf("20 Questions (M) Mode!\n");
    char name[35];
    int score = 0;
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1] = 0;// remove end characterxe
    int clientNum = 1; // for numbering questions in transcript
    struct player* c = newStruct(name,score);



    clientLogicMultiple(c, IP);
  }



}
