////Родитель передает потомку строку с различными символами, потомок возвращает только цифры, если цифр нет, то возвращает слово «No»
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/msg.h>
//#include <sys/ipc.h>
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <signal.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <sys/mman.h>
//
//void handler1(int i)
//{
//    signal(SIGUSR1, handler1);
//    printf("\nРодительский процесс отправил SIGUSR1 дочернему!\n\n");
//}
//
//void handler2(int i){
//    signal(SIGUSR1, handler1);
//    printf("\nДочерний процесс отправил SIGUSR1 дочернему!\n\n");
//}
//
//
//int main(void){
//    size_t pagesize = getpagesize();
//    char numbers[10] = "1234567890";
//    int fd, result;
//    char *region;
//
//    printf("System page size: %zu bytes\n", pagesize);
//
//    signal(SIGUSR1, handler1); //посылаем сигнал дочернему процессу
//
//    //создание файла для общего доступа
//    fd = open("text.txt", O_RDWR|O_CREAT, 0777);
//
//    if(fd < 0)
//    {
//        printf("Can\'t open\n");
//        return -1;
//    }
//
//    write (fd,"/0", sizeof(char));
//    region=(char*)mmap(NULL,pagesize,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); //сделали общий файл
//    //если не получилось сделать map
//    if (region == MAP_FAILED)
//    {
//        perror("Could not mmap");
//        return -1;
//    }
//    char *stroka="1qwertop2sdfghjkl";
//    region = stroka;
//    result=fork();
//    if(result<0)
//    {
//        printf("Can't fork child\n");
//        return -1;
//    }
//
//    else if (result > 0) //родитель
//    {
//        kill(result,SIGUSR1);
//        sleep(8);
//        signal(SIGUSR1, handler1);
//        printf("Numbers: ");
//        if(strcmp(region,"") == 0){
//            printf("No!\n");
//        }
//        else{
//            printf("%s\n",region);
//        }
//    }
//    else //дочерний
//    {
//        signal(SIGUSR1, handler2); //дочерний процесс получил сигнал от родительского
//        char *s = region;
//        char str[] = ""; //строка, которую будем выводить
//
//        printf("Shared file info: %s \n",s);
//        for(int i=0; i<strlen(s);i++){
//            if(strchr(numbers, s[i]) != NULL){ //если символ - цифра
//                strcpy(str, &s[i]); //копируем
//            }
//        }
//        //отправляем информацию в общий файл
//        strcpy(region, str);
//        printf("%s\n",region);
//
//        kill(getppid(),SIGUSR1);
//        printf("Child exit\n");
//
//    }
//    return 0;
//}


#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void handler()
{
    printf("Родительский процесс передал данные дочернему\n");
}

void handler1()
{
    printf("Дочерний процесс передал данные родительскому\n");
}


int main(void)
{
    (void) signal(SIGUSR1, handler); //сигнал о передаче данных дочернему процессу
    int fd, result;
    char *region;
    size_t pagesize = getpagesize();
    char numbers[10] = "1234567890";
    
    
    fd = open("text.txt", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        printf("Can\'t open shm\n");
        return -1;
    }
    
    write (fd,"/0", sizeof(char));
    region=(char*)mmap(NULL,pagesize,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    
    char *stroka="qwertopsdfghjkl";
    region = stroka;
    
    if (region == MAP_FAILED)
    {
        perror("Could not mmap");
        return -1;
    }
    
    result=fork();
    if(result<0)
    {
        printf("can't fork child\n");
        return -1;
    }
    else if (result > 0)
    {
        //родительский процесс
        sleep(3);
        kill(result, SIGUSR1);
        sleep(3);
        (void) signal(SIGUSR1, handler1); //сигнал о том, что родительскому процессу были переданы данные из дочернего
        sleep(8);
        printf("Nubmers: ");
        printf("%s\n",region);
        printf("Parent exit\n");
    }
    else
    {
        //дочерний процесс
        char *s = region;
        char str[] = "";
        
        printf("Shared file info: %s \n",s);
        
        for(int i=0; i<strlen(s);i++){
            if(strchr(numbers, s[i]) != NULL){ //если символ - цифра
                strcpy(str, &s[i]); //копируем
            }
        }
        printf("str: ");
        printf("%s\n",str);
        
        //отправляем информацию в общий файл
        if(strcmp(str, "")==0){
            strcpy(region, "NO");
        }
        else{
            strcpy(region, str);
        }
        printf("%s\n",region);
        
        kill(getppid(), SIGUSR1);
        printf("Child exit\n");
    }
    return 0;
}
