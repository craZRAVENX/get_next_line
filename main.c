#include "get_next_line.h"
#include <stdio.h>


int main()
{
    int fd = open("mant.txt", O_WRONLY);
    char *buffer = malloc(2);
    int a = read(fd, buffer, 1);
    printf("\n");
    do 
    {
        printf("%c", *buffer);
        a = read(fd, buffer, 1);
        if (a == -1)
            break;
    } while (*buffer != '\0');

}

