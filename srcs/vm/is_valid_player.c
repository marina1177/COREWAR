#include "../../includes/vm.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../includes/op.h"
# define NULL_SIZE 4
# define CHAMP_NAME_SIZE 128
# define CHAMP_COMM_SIZE 2048

unsigned int	get_integer(int fd)
{
	int a;
	char *buffer;
	
	buffer = (char *)malloc(sizeof(char) * 4);	
	read(fd, buffer, 4);
	a = (unsigned char)(buffer[0]) << 24 |
		(unsigned char)(buffer[1]) << 16 |
		(unsigned char)(buffer[2]) << 8 |
		(unsigned char)(buffer[3]);
	free(buffer);
	return (a);
}


static char		*get_string(int fd, int len)
{
	char *s;


	return (1);
}

int		is_dot_cor_name(char *name)
{
	int i;

	i = ft_strlen(name) - 1;
	if (name[i] == 'r' && name[i - 1] == 'o' && name[i - 2] == 'c' && name[i - 3] == '.')
		return (0);
	else
		return (1);
}

int	is_valid_player(char *arg, t_vm *vm, t_player *player)
{
	char	*s;
	int		fd;	

	if ((fd = open(arg, O_RDONLY)) == -1)
		handle_error_vm(asprintf(&s, "unable to open file %s", arg), vm);
	if (!is_dot_cor_name(arg))
		handle_error_vm(asprintf(&s, "player name %s must contain '.cor' extension'.\n \
			 There is no strict rule about VM validation in subject file, but \
			 properly compiled bytecode file must have '.cor' extension.", arg), vm);
	if (get_integer(fd) != COREWAR_EXEC_MAGIC)
		handle_error_vm(asprintf(&s, "invalid magic code in file %s", arg), vm);
	//нулевое имя чемпиона?
	player->name = get_string(fd, CHAMP_NAME_SIZE);	
	get_integer(fd) ? handle_error("No NULL") : 0;
	player->code_size = get_integer(fd);
	player->comment =  get_string(fd, CHAMP_COMM_SIZE);
	get_integer(fd) ? handle_error("No NULL") : 0;
	player->code = get_string(fd, player->code_size);
	return (1);
}