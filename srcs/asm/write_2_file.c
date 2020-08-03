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

int 	write_2_file(t_dasm *ds, char *name)
{
	int		new_fd;
	int		error;

	close(ds->fd);
	error = 1;
	if ((new_fd = create_file(name)) > 0)
	{
		error = write(new_fd, ds->name, ft_strlen(ds->name));
		error = write(new_fd, "\n\n", 2);
		error = write(new_fd, ds->comment, ft_strlen(ds->comment));
		error = write(new_fd, "\n\n", 2);
		error = write(new_fd, ds->champ_code, ft_strlen(ds->champ_code));
		close(new_fd);
		if (error > 0)
			return (1);
		else
		{
			char *error_buf = strerror(errno);
			printf(" Error message -> %s", error_buf);
		}
	}
	return (0);
}
