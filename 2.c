#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SEM_NAME_1 "/semaphore1"
#define SEM_NAME_2 "/semaphore2"


int main()
{
    sem_t *semaphore, *mutex;
    time_t timer = 0;
    
    mutex=sem_open(SEM_NAME_1,0);
    semaphore=sem_open(SEM_NAME_2,0);
    
    for(int i=0;i<5;i++){
        sem_wait(mutex);
        if(sem_getvalue(semaphore, &timer) == -1){
            printf("Error in get value");
        }
        printf("Текущее время2: %s", ctime(&timer));
        sem_post(mutex);
        sleep(1);
    }
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
    
}

