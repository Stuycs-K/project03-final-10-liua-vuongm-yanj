#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <dirent.h>
#include <signal.h>

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};
int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

int main(){
    printf("%s\n" , "Write");

    // Display a message indicating that it attempting to open the resource. This means there will be some message prior to the program blocking.
    printf("Attempting to access semaphore... \n");
    
    // Will attempt to access the resources using the semaphore.
    // accessing and decreasing by one
    int semid = semget(696, 1 , 0);
    struct sembuf sb; 
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop(semid, &sb , 1);


    printf("Add another line to the story : ");
    char userInput[100];
    // Read the user input from stdin
    fgets(userInput, sizeof(userInput), stdin);

    // increasing by one and returning
    // After completing these steps you release the semaphore, and end the write program.
    sb.sem_op = 1;
    semop(semid, &sb, 1);
}