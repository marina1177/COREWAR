/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:17:24 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:17:25 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	ft_exit(char *line)
{
	ft_printf("%s", line);
	exit(0);
}

int			is_integer(char *s)
{
	size_t	len;
	int		n;

	n = ft_atoi(s);
	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || (int)len != ft_ilen(n))
		return (0);
	if (s[0] == '-' && len == 1)
		return (0);
	return (1);
}
