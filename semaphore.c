#include "semaphore.h"

int semSetup(int max){
    int semd;
    semd = semget(KEY, 1, IPC_CREAT| 0644);
    union semun us;
    us.val = max;
    int r = semctl(semd, 0, SETVAL, us);
    return semd;
}


void accessSemaphore(){
    int semid = semget(KEY, 1,0);
    struct sembuf sb; 
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;


    int c = semctl(semid, 0 , GETVAL, 0);

    printf("Value of sem before decrementing:%d \n", c);
    semop(semid, &sb , 1);
    c = semctl(semid, 0 , GETVAL, 0);
    printf("Value of sem after decrementing:%d \n", c);
}

void releaseSemaphore(){
    // setting up semaphore ID and struct
    int semid = semget(KEY, 1,0);
    struct sembuf sb;
    // release semaphore 
    sb.sem_op = 1;
    int c = semctl(semid, 0 , GETVAL, 0); 
    printf("Value of sem before incrementing:%d \n", c);

    semop(semid, &sb, 1);
    c = semctl(semid, 0 , GETVAL, 0);    
    printf("Value of sem after incrementing:%d \n", c);
}
