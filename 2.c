////Первый процесс семафорами передаёт второму текущее время, а второй выводит его в форматированном для человека виде. Внимание: никаких средств взаимодействия(файлов, pipe, ...), кроме семафоров и мьютексов, не использовать!

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
    int zn;
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0777, 0);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 0);
    for(int i = 0; i < 5; i++){
        sem_wait(semaphore2);
//        sleep(1);
        sem_getvalue(semaphore1, &zn);
//        sem_wait(semaphore2);
        printf("Programm2 gets simbol: %d\n", zn);
        printf("\n");
        sleep(1);
        sem_post(semaphore1);
    }
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
}
