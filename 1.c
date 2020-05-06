#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SEM_NAME_1 "/semaphore1"
#define SEM_NAME_2 "/semaphore2"

int main() {
    time_t timer = time(NULL);
    time_t semtimer = 0;
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0777, timer);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 0);
    sem_post(semaphore2);
    
    for(int i=0;i<5;i++){
        sem_getvalue(semaphore1, &semtimer);
        timer = time(NULL);
        for(int i=0; i< (timer - semtimer); i++){
            sem_post(semaphore1);
        }
        printf("Tekuschee vremya: %ld\n", timer);
        sleep(1);
        sem_post(semaphore2);
        
    }
    
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
    
}

//#include <unistd.h>
//#include <semaphore.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <stdlib.h>
//
//int main(void)
//{
//    time_t timer;
//    time_t semtimer;
//
//    sem_t *sem1 = sem_open("sem1", O_CREAT, 0777, 0);
//    sem_t *sem2 = sem_open("data", O_CREAT, 0777, 0);
//
//    while (1)
//    {
//        timer = time(NULL);
//        printf("Current time in 1 proc: %ld  ",timer);
//        sem_getvalue(sem1, &semtimer);
//        for (int i = 0; i < (timer - semtimer); i++) {
//            sem_post(sem2);
//        }
//        sem_post(sem1);
//    }
//    sem_unlink("sem1");
//    sem_unlink("data");
//    return(0);
//}
