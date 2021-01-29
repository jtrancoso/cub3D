#include <fcntl.h>

int main(void)
{
	int fd;
	char BUFFER[1000];

	fd = open("645620.bmp", O_RDONLY);
	read(fd, BUFFER, 14);

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 8; j++)
			printf("%d", !!(*(BUFFER + i) << j >> 7));
		printf("\n");
	}

}