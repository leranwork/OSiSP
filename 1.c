//#include <unistd.h>
//#include <sys/types.h>
//#include <semaphore.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>
//#define SEM_NAME_1 "/semaphore1"
//#define SEM_NAME_2 "/semaphore2"
//int main(){
//
//    sem_t *semaphore, *mutex;
//    time_t timer = 0;
//
//    mutex=sem_open(SEM_NAME_1,O_CREAT,0777,1);
//    semaphore=sem_open(SEM_NAME_2,O_CREAT,0777,1);
//
//    printf("0\n1\n");
//
//    for(int i=0;i<5;i++){
//        sem_wait(mutex);
//
//        if(sem_getvalue(semaphore, &timer) == -1){
//            printf("ERROR in get value\n");
//        }
//        timer = time(NULL); //вычисляем текущее время
//        printf("Текущее время1: %ld \n", timer);
//        sem_init(semaphore,0,(int)timer);
//
//        sem_post(mutex);
//        sleep(1);
//    }
//    sem_unlink(SEM_NAME_1);
//    sem_unlink(SEM_NAME_2);
//    return 0;
//}
//


//#include <stdio.h>
//#include <time.h>
//#include <semaphore.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <string.h>
//
//int main(void){
//    
//    sem_t *sem1, *sem2, *sem3;
//    printf("1");
//    if((sem1 = sem_open("sig5", O_CREAT, 0777, 0)) == SEM_FAILED){
//        printf("Error in sem_open1");
//    };
//    printf("1");
//
//    if((sem2 = sem_open("sig6", O_CREAT, 0777, 1)) == SEM_FAILED){
//        printf("Error in sem_open2");
//    };
//    printf("1");
//    if((sem3 = sem_open("data3",O_CREAT, 0777, 0)) == SEM_FAILED){
//       printf("Error in sem_open3");
//    }
//    
//    time_t timer;
//    
//    for(int i=0; i<10;i++){
//        sem_wait(sem2);
//        timer = time(NULL);
//        printf("Текущее время: %ld",timer);
//        
//        for(int i=0;i<(int)timer;i++){
//            sem_post(sem3);
//        }
//        sem_post(sem1);
//        sleep(1);
//    }
//    
//    sem_unlink("sig5");
//    sem_unlink("sig6");
//    sem_unlink("data3");
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
//    struct tm *u;
//    char *f;
//    const time_t timer=time(NULL);
//    u=localtime(&timer);
//    f=asctime(u);
//    char semaphore[]="/semaphore";
//    sem_t *s=sem_open(semaphore,O_CREAT,0777,1);
//    int file=0;
//    sem_wait(s);
//    if((file=open("tß.txt",O_RDWR))==-1)
//    {
//        printf("Open failed");
//        exit(-1);
//    }
//    write(file,u,100);
//    printf("Process 1 write %d\n ",u);
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
    time_t semtimer ;
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0777, timer);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 0);
    sem_post(semaphore2);
    
    for(int i=0;i<5;i++){
        sem_getvalue(semaphore1, semtimer);
        timer = time(NULL);
        for(int i=0; i< (timer - semtimer); i++){
            sem_post(semaphore1);
        }
//        sem_wait(semaphore1);
        printf("Tekuschee vremya: %ld\n", timer);
        sem_post(semaphore2);
    
    }
    
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
    
}
