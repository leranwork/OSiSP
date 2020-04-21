//Родитель передает потомку строку с различными символами, потомок возвращает только цифры, если цифр нет, то возвращает слово «No»
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

int main(void){
    char numbers[10] = "1234567890";
    int fd, result;
    char *region;
    int catet1 = 25, catet2 = 47;
    printf("System page size: %u bytes\n", catet1);
    //создание файла для общего доступа
    fd = open("text.txt", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        printf("Can\'t open shm\n");
        return -1;
    }

    write (fd,"/0", sizeof(char));
    region=(char*)mmap(NULL,catet1,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    //если не получилось сделать map
    if (region == MAP_FAILED)
    {
        perror("Could not mmap shm");
        return -1;
    }
    
    result=fork();
    if(result<0)
    {
        printf("cant fork child\n");
        return -1;
    } else if (result > 0)
    {
        //родитель
        kill(result,0);
        sleep(3);
        printf("Parent exit\n");
    }
    else
    {
        //дочерний
        char *s = region;
        printf("!!! %s \n", region);
        char *str = NULL; //строка, которую будем выводить
        printf("Shared file info: %s \n",s);
        for(int i=0; i<strlen(s);i++){
            if(strchr(numbers, s[i]) != NULL){ //если символ - цифра
                strcat(str, &s[i]); //копируем
            }
        }
            if(str == NULL){
                printf("NO!\n"); //если в строке нет цифр
            }
            else {
                printf("Numbers: %s \n",str);
            }
        kill(getppid(),0);
        printf("Child exit\n");
    }
    return 0;
}
