
void accessSemaphore(int semid){
    struct sembuf sb; 
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop(semid, &sb , 1);
}

void releaseSemaphore(int semid){
    // setting up semaphore ID and struct
    int semid = semget(694, 1 , 0);
    struct sembuf sb;
    // release semaphore 
    sb.sem_op = 1;
    semop(semid, &sb, 1);
}
