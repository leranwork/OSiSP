//#include <semaphore.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <string.h>
//#define SEM_NAME_1 "/semaphore1"
//#define SEM_NAME_2 "/semaphore2"
//
//
//int main()
//{
//    sem_t *semaphore, *mutex;
//    time_t timer = 0;
//
//    mutex=sem_open(SEM_NAME_1,O_RDWR,0);
//    semaphore=sem_open(SEM_NAME_2,O_RDWR,1);
//
//    for(int i=0;i<5;i++){
//        sem_wait(mutex);
//        if(sem_getvalue(semaphore, &timer) == -1){
//            printf("Error in get value");
//        }
//        printf("Текущее время2: %s", ctime(&timer));
//        sem_close(semaphore);
//        sem_post(mutex);
//        sleep(1);
//    }
//    sem_unlink(SEM_NAME_1);
//    sem_unlink(SEM_NAME_2);
//    return 0;
//
//}
//

//#include <semaphore.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <string.h>
//
//int main(void){
//
//    printf("1");
//    sem_t *sem1 = sem_open("sig5", O_RDWR,1);
//    printf("2");
//    sem_t *sem2 = sem_open("sig6", O_RDWR);
//    printf("3");
//    sem_t *sem3 = sem_open("data3", O_RDWR);
//
//    for(int i=0;i<10;i++){
//        sem_wait(sem1);
//        time_t timer;
//        sem_getvalue(sem3, &timer);
//        int count = (int)timer;
//
//        while(count!=0){
//            sem_wait(sem3);
//            count--;
//        }
//
//        printf("Текущее время2: %s", ctime(&timer));
//
//        sem_post(sem2);
//        sleep(1);
//    }
//    return 0;
//}

//#include <semaphore.h>
//#include <stdio.h>
//#include <time.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <unistd.h>
//int main()
//{
//    char f[25];
//    char semaphore[]="/semaphore";
//    sem_t *s=sem_open(semaphore,O_RDWR,0777);
//    int file=0;
//    sem_wait(s);
//    if((file=open("t.txt",O_RDWR))==-1)
//    {
//        printf("Open failed");
//        exit(-1);
//    }
//    read(file,f,25);
//    printf("Process 2 read: %s\n",asctime(f));
//    close(file);
//    sem_post(s);
//    sem_close(s);
//    return 0;
//}

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
    int count = 0;
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_EXCL);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_EXCL);
    for(int i=0; i<5;i++){
        sem_wait(semaphore2);
        sem_getvalue(semaphore1, timer);
        printf("Prinyatiy vremya: %s \n", ctime(&timer));
        sleep(1);
        sem_post(semaphore1);
    }
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
    
}
