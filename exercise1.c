#include "get_next_line.h"

// fark ettiysen her read kullandigimizda son kaldigi yerden okuyor. test edebilirsin.
int main ()
{
	int fd = open("test.txt", O_RDONLY);
	// int resfd = open("result", O_RDWR);
	char string[5];
	char str[5];
	int a = read(fd, string, BUFF_SIZE);
	int b = read(fd, str, BUFF_SIZE);
	string[a] = '\0';
	str[b] = '\0';
	close(fd);
	printf("%s %s",string, str);
}