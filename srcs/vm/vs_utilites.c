/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_utilites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 16:12:17 by clala             #+#    #+#             */
/*   Updated: 2020/07/03 16:12:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		count_dig(size_t val)
{
	int		i;
	size_t	n;

	i = 0;
	n = val;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		vs_putstr_fd(int fd, const char *s)
{
	size_t i;

	if (!s || !*s)
		return (0);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}

int		vs_strcpy(char *dest, const char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = dest;
	while (*src)
	{
		*(temp++) = *(src++);
		i++;
	}
	*temp = '\0';
	return (i);
}

void	vs_print_error(t_vm *vm, char *error_msg)
{
	if (vm->mods->vs && vm->vs->fd)
		dprintf(vm->vs->fd, "%s\n", error_msg);
}
