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
int main(){
    
    sem_t *semaphore, *mutex;
    time_t timer = 0;
    
    mutex=sem_open(SEM_NAME_1,O_CREAT,0777,1);
    semaphore=sem_open(SEM_NAME_2,O_CREAT,0777,1);
    
    printf("0\n1\n");

    for(int i=0;i<5;i++){
        sem_wait(mutex);
        
        if(sem_getvalue(semaphore, &timer) == -1){
            printf("ERROR in get value\n");
        }
        timer = time(NULL); //вычисляем текущее время
        printf("Текущее время1: %ld \n", timer);
        sem_init(semaphore,0,(int)timer);
        
        sem_post(mutex);
        sleep(1);
    }
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
}


