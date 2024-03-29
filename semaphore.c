#include "semaphore.h"

// int main(){
//     int semd;
//     semd = semget(694, 1, IPC_CREAT | IPC_EXCL | 0644);
//     union semun us;
//     us.val = 1;
//     int r = semctl(semd, 0, SETVAL, us);
// }


void accessSemaphore(int semid){
    struct sembuf sb; 
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop(semid, &sb , 1);
}

void releaseSemaphore(int semid){
    // setting up semaphore ID and struct
    struct sembuf sb;
    // release semaphore 
    sb.sem_op = 1;
    semop(semid, &sb, 1);
}
