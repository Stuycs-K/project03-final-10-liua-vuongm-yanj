#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
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
            


void printFile (char filename[]){
    FILE *file = fopen("story.txt", "r");
    char buffer [100];

    while(fgets(buffer, sizeof(buffer), file) != NULL){
        printf("%s", buffer);
    }
    fclose(file);
}

int main(int argc, char *argv[]){

    int semd; // semaphore

    if (argv[1] == NULL)
    {
        printf("Input either create, remove, or view\n");
    }

    // Should make the shared memory, semaphore and file (open the file with the truncate flag).
    // Set any values that are needed.
    else if (strcmp("create", argv[1]) == 0)
    {
        printf("create ran\n");
        // semaphore
        semd = semget(696, 1, IPC_CREAT | 0644);
        union semun us;
        us.val = 1;
        int r = semctl(semd, 0, SETVAL, us);
    }

    // Remove the shared memory and the semaphore
    // Display the full contents of the story.
    else if (strcmp("remove", argv[1]) == 0){
        printf("remove ran");
        semctl(semd, 0 , IPC_RMID, 0);
        printFile("story.txt");
    }

    // Display the full contents of the story.
    else if (strcmp("view", argv[1]) == 0){
        printFile("story.txt");
    }
}