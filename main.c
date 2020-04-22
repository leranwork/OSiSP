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

void handler()
{
    printf("Родительский процесс передал данные дочернему\n");
}


int main(void)
{
    signal(SIGUSR1, handler); //сигнал о передаче данных дочернему процессу
    int fd, result;
    char *region;
    char numbers[] = "1234567890";
    int j=0;
    size_t pagesize = getpagesize();
    
    fd = open("text.txt", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        printf("Can\'t open shm\n");
        return -1;
    }
    
    write (fd,"/0", sizeof(char));
    region=(char*)mmap(NULL,pagesize,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    
    char *stroka="qwertops1dfg5hjkl";
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
        kill(result, SIGUSR1);
        signal(SIGUSR1, handler); //сигнал о том, что родительскому процессу были переданы данные из дочернего
        sleep(8);
        printf("Nubmers: ");
        printf("%s\n",region);
        printf("Parent exit\n");
    }
    else
    {
        printf("child process\n");
        //дочерний процесс
        char *s = region;
        char str[20] = "NO";
        
        printf("Shared file info: %s \n",s);
        
        for(int i=0; i<strlen(s);i++){
            if(strchr(numbers, s[i]) != NULL){ //если символ - цифра
                str[j++] = s[i]; //копируем
            }
        }
        printf("a: %s\n",str);
        
        strcat(region, str);
        
        if (msync(region, strlen(region), MS_SYNC) == -1)
        {
            perror("Could not sync the file to disk");
        }
        
        if (munmap(region, strlen(region)) == -1)
        {
            close(fd);
            perror("Error un-mmapping the file");
            exit(EXIT_FAILURE);
        }
        
        close(fd);
        kill(getppid(), 0);
        printf("Child exit\n");
    }
    return 0;
}
