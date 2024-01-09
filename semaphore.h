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

#define KEY 1923

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short  *array; 
  struct seminfo  *__buf;
};

int semSetup();
void accessSemaphore(int semid);
void releaseSemaphore(int semid);
