# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/op.h"

int main(int ac, char **av)
{
	int a;
	int fd;
	char *buffer = (char *)malloc(sizeof(char) * 4);

	fd = open(av[1], O_RDONLY);
	read(fd, buffer, 4);

	a = (unsigned char)(buffer[0]) << 24 |
				(unsigned char)(buffer[1]) << 16 |
				(unsigned char)(buffer[2]) << 8 |
				(unsigned char)(buffer[3]);
	printf("%d", a == COREWAR_EXEC_MAGIC);
	return (0);
}
