#include "../../includes/vm.h"

void	read_data(char *filename, t_player *player)
{
	int ret;
	int	fd;
	int i = 0;
	unsigned int exec_begin = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	char buf[exec_begin + 1];

	if ((fd = open(filename, O_RDONLY, 0)) < 0)
		printf(ERR_FOPEN);
	player->exec = (char *)malloc(sizeof(char) * 683);
	ft_bzero(player->exec, 683);
	while ((ret = read(fd, buf, exec_begin)) > 0)
	{
		buf[ret] = '\0';
		++i;
		if (i == 2){
			player->exec = (char*)ft_memcpy(player->exec, buf, ret);
			player->exec[ret] = '\0';
			//print_memory(player->exec, ret);
		}
	}
	close(fd);
}

void	clean_data(t_vm *data)
{
	int i = 1;
	ft_strdel((char **)&data->arena);
	free(data->players);
	data->players = NULL;
	while (data->carriages)
	{
		del_carriage(&data->carriages, data->carriages);
		//printf("%d\n", i);
		i++;
	}
}

void	ft_exit(char *line)
{
	printf(line);
	exit(0);
}
