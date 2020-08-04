/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_2_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 14:27:50 by root              #+#    #+#             */
/*   Updated: 2020/08/03 22:37:03 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

static int	write_name(int fd, t_dasm *ds)
{
	int		k;

	k = 0;
	k += write(fd, ".name \"", 7);
	k += write(fd, ds->name, ft_strlen(ds->name));
	k += write(fd, "\"\n", 2);
	return (k);
}

static int	write_comment(int fd, t_dasm *ds)
{
	int		k;

	k = 0;
	k += write(fd, ".comment \"", 10);
	k += write(fd, ds->comment, ft_strlen(ds->comment));
	k += write(fd, "\"\n", 2);
	return (k);
}

int			write_2_file(t_dasm *ds, char *name)
{
	int		new_fd;
	int		error;

	close(ds->fd);
	error = 1;
	if ((new_fd = create_file(name)) > 0)
	{
		error = write_name(new_fd, ds);
		error = write_comment(new_fd, ds);
		error = write(new_fd, "\n", 2);
		error = write(new_fd, ds->champ_code, ft_strlen(ds->champ_code));
		close(new_fd);
		if (error > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
