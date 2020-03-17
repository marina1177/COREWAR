#include "../includes/vm.h"# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/op.h"
# define NULL_SIZE 4
# define CHAMP_NAME_SIZE 128
# define CHAMP_COMM_SIZE 2048

int get_integer(int fd)
{
	int a;
	int fd;
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


static int		get_string()
{
	return (1);
}

static int		get_integer()
	size_t flag)
{
	int		code;
	unsigned int buffer[4];

	
	int a = (unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]);
	if (flag == 1 && code != COREWAR_EXEC_MAGIC)
		handle_error("");
		
	/*if (flag == 2 && code > CHAMP_MAX_SIZE)
		ret_file_error("Error: size of exec_code more than MAX_SIZE ",
			player->filename, "\n", -1);*/
	return (code);
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

int	is_valid_player(char *player)
{
	char *s;
	int		fd;
	int		player_code_size;
	char	*player_code;

	if ((fd = open(player, O_RDONLY)) == -1)
		handle_error(sprintf("unable to open file %s"));
	if (!is_dot_cor_name(player))
		handle_error(asprintf("player name %s must contain '.cor' extension'.\n \
			 There is no strict rule about VM validation in subject file, but \
			 properly compiled bytecode file must have '.cor' extension."));
	if (get_integer(fd) != COREWAR_EXEC_MAGIC)
		handle_error("invalid magic code in file");
	//нулевое имя чемпиона?
	get_string(fd, CHAMP_NAME_SIZE) ? 1 : 0;
	get_integer(fd) ? handle_error("No NULL") : 0;
	player_code_size = get_integer(fd);
	get_string(fd, CHAMP_COMM_SIZE);
	get_integer(fd) ? handle_error("No NULL") : 0;
	get_string(fd, player_code_size);
	player_code = (char *)malloc(sizeof(char) * player_code_size);
	player_code = get_string(fd, player_code_size);
	return (1);
}