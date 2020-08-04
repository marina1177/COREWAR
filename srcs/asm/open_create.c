/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/08/03 22:37:03 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

int		open_file(char *name)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) > 0)
	{
		return (fd);
	}
	return (-1);
}

char	*create_new_name(char *name)
{
	char	*dot_in;
	char	*new_name;

	if ((dot_in = ft_strchr(name, '.')))
	{
		*dot_in = '\0';
		if ((new_name = ft_strjoin(name, _DOT_COR_)))
			return (new_name);
	}
	return (NULL);
}

int		create_file(char *name)
{
	int		new_fd;
	char	*new_name;

	if ((new_name = create_new_name(name)))
	{
		new_fd = open(new_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (new_fd > 0)
			return (new_fd);
		else
			return (0);
	}
	return (0);
}
