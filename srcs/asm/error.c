/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 17:03:23 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 17:12:07 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

void		put_error(char *err, int type)
{
	if (type)
	{
		ft_printf("%s [%d:%d]\n", err, g_mdata->y, g_mdata->x);
		errno = EINVAL;
	}
	else
	{
		ft_printf("%s\n", err);
	}
	free_data();
	exit(errno);
}

void		print_error(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
	{
		perror(message);
	}
	free_data();
	exit(1);
}

void		error_line(char *event, char *line, int x)
{
	ft_printf("event_%s_x_%d\n", event, x);
	ft_strdel(&line);
	free_data();
	exit(1);
}

void		error_event(char *event)
{
	ft_putstr_fd(RED, 2);
	if (errno == 0)
		ft_putendl_fd(event, 2);
	else
		perror(event);
	ft_putstr_fd(EOC, 2);
	free_data();
	exit(1);
}

void		error(void)
{
	char *s;

	s = "Error\n";
	write(2, s, ft_strlen(s));
	free_data();
	exit(0);
}
