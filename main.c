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
#include <ctype.h>

void handler(int idsignal)
{
    
    if (idsignal==0) {
        printf("Родительский процесс передал данные дочернему\n");
        idsignal++;
    }
    else {
        printf("Дочерний процесс передал данные родительскому\n");
        idsignal--;
    }
}


int main(void)
{
    
    int fd, result;
    char *region;
    char stroka[1024];
    char numbers[] = "1234567890";
    int j=0;
    size_t pagesize = getpagesize();
    signal(SIGUSR1, handler); //сигнал о передаче данных дочернему процессу
    
    fd = open("text.txt", O_RDWR|O_CREAT, 0777);
    
    if(fd < 0)
    {
        printf("Can\'t open \n");
        return -1;
    }
    
    write (fd,"/0", sizeof(char));
    region=(char*)mmap(NULL,pagesize,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (region == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    
    
    result=fork();
    if(result<0)
    {
        printf("can't fork child\n");
        return -1;
    }
    else if (result > 0)
    {
        printf("Введите строку: ");
        gets(stroka);
        strcpy(region, stroka);
        //родительский процесс
        kill(result, SIGUSR1);
        signal(SIGUSR1, handler); //сигнал о том, что родительскому процессу были переданы данные из дочернего
        sleep(8);
        printf("Информация, полученная родительским процессом: ");
        printf("%s\n",region);
        printf("Выход из родительского процесса\n");
        if (munmap(region, pagesize) <0 )
        {
            perror("Could not munmap"); return -1;
        }
    }
    else
    {
        sleep(10);
        printf("Дочерний процесс\n");
        //дочерний процесс
        char *s = region;
        char str[20] = "NO";
        
        printf("Информация, полученная из родительского процесса: %s \n",s);
        
        for(int i=0; i<strlen(s);i++){
            if(strchr(numbers, s[i]) != NULL){ //если символ - цифра
                str[j++] = s[i]; //копируем
            }
        }
        
        printf("Информация, отправляемая родительскому процессу: %s\n",str);
        strcpy(region, str);
        close(fd);
        kill(getppid(), SIGUSR1);
        printf("Выход из дочернего процесса\n");
    }
    
    return 0;
}
