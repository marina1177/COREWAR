/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/04/07 14:17:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int		read_byte(char *byte, int size, int fd)
{
	unsigned char	c;
	int				i;
	int			error;
	error = 1;
	c = 0;
	i = size - 1;
	while (i >= 0 && error > 0)
	{
		error = read(fd, &c, 1);
		byte[i] = c;
		i--;
	}
	if (error > 0)
		return (1);
	return (0);
}

int		read_champion_comment(t_dasm *as, int fd)
{
	int		i;
	char	*comment;

	if (!(comment = (char*)malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (0);
	if ((i = read(fd, comment, COMMENT_LENGTH)) == COMMENT_LENGTH)
	{
		comment[i] = '\0';
		as->comment = comment;
		return (1);
	}
	return (0);
}

int		read_champion_name(t_dasm *as, int fd)
{
	int		i;
	char	*name;

	if (!(name = (char*)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		return (0);
	if ((i = read(fd, name, PROG_NAME_LENGTH)) == PROG_NAME_LENGTH)
	{
		name[i] = '\0';
		as->name = name;
		return (1);
	}
	return (0);
}

int		champion_code_size(t_dasm *as, int fd)
{
	unsigned int	size;
	char	*bt;

	bt = (char*)&size;
	if (read_byte(bt, 4, fd) && size > 0)
	{
		as->champ_code_size = size;
		return (1);
	}
	return (0);
}
