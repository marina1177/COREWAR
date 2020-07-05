/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:17:40 by clala             #+#    #+#             */
/*   Updated: 2020/07/05 14:24:32 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#define NULL_SIZE 4
#define INT_SIZE 4
#define CH_NAME_SIZE 128
#define CH_COMM_SIZE 2048

static char		*valid_read(int fd, char *arg, int len, t_vm *vm)
{
	char		*s;
	int			check_read;

	s = (char *)ft_memalloc(len);
	check_read = read(fd, s, len);
	check_read != len ? handle_error_str_arg(ERR_CH_FSIZE, arg, vm) : 1;
	return (s);
}

static char		*terminated(char *s, int len)
{
	char		*terminated;

	terminated = ft_strnew(len);
	ft_memcpy(terminated, s, len);
	free(s);
	return (terminated);
}

int				get_integer(int fd, char *arg, t_vm *vm)
{
	int			a;
	char		*buffer;

	a = 0;
	buffer = valid_read(fd, arg, INT_SIZE, vm);
	if (buffer)
	{
		a = (unsigned char)(buffer[0]) << 24 |
			(unsigned char)(buffer[1]) << 16 |
			(unsigned char)(buffer[2]) << 8 |
			(unsigned char)(buffer[3]);
		free(buffer);
	}
	return (a);
}

int				is_dot_cor_name(char *name)
{
	int			i;

	i = ft_strlen(name) - 1;
	if (name[i] == 'r' && name[i - 1] == 'o' &&
		name[i - 2] == 'c' && name[i - 3] == '.')
		return (1);
	else
		return (0);
}

int				parse_player(t_vm *vm, char *arg, t_player *player)
{
	char		*s;
	int			fd;

	s = NULL;
	if ((fd = open(arg, O_RDONLY)) == -1)
		handle_error_str_arg(ERR_FOPEN, arg, vm);
	read(fd, s, 0) < 0 ? handle_error_str_arg(ERR_READING, arg, vm) : 1;
	!is_dot_cor_name(arg) ? handle_error_str_arg(ERR_FNAME, arg, vm) : 0;
	if (get_integer(fd, arg, vm) != COREWAR_EXEC_MAGIC)
		handle_error_str_arg(ERR_MAGIC, arg, vm);
	player->name = terminated(valid_read(fd, arg, CH_NAME_SIZE, vm),
							CH_NAME_SIZE);
	get_integer(fd, arg, vm) ? handle_error_str_arg(ERR_NO_NULL, arg, vm) : 0;
	player->code_size = get_integer(fd, arg, vm);
	if (player->code_size > CHAMP_MAX_SIZE)
		handle_error_str_arg(ERR_BIGEX, arg, vm);
	player->comment = terminated(valid_read(fd, arg, CH_COMM_SIZE, vm),
								CH_COMM_SIZE);
	get_integer(fd, arg, vm) ? handle_error_str_arg(ERR_NO_NULL, arg, vm) : 0;
	player->code = valid_read(fd, arg, player->code_size, vm);
	s = ft_strnew(1);
	if (read(fd, s, 1) && ft_free("1", s))
		handle_error_str_arg(ERR_BIGEX, arg, vm);
	free(s);
	return (1);
}
