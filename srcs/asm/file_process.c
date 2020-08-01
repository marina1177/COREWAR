/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:15:00 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 16:15:45 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	valid_filename(char *fname)
{
	int			i;

	i = 0;
	while (fname[i])
		i++;
	while (fname[--i])
		if (fname[i] == '.')
			break ;
	if (ft_strcmp(&fname[i], ".s"))
		error_event(ERR_FNAME);
}

void	read_file(char *filename)
{
	int	fd_s;

	valid_filename(filename);
	if ((fd_s = open(filename, O_RDONLY, 0)) == -1)
	{
		error_event(ERR_FOPEN);
	}
	data_init();
	g_mdata->filename = filename;
	g_mdata->fd_s = fd_s;
	parse_file(fd_s);
	close(fd_s);
	compilation();
	free_data();
}
