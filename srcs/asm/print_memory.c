/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:59:04 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/29 17:11:41 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

static void	part_1(size_t i, size_t *add_j, size_t size, unsigned char *ptr)
{
	size_t	j;

	j = *add_j;
	while (j < 16 && i + j < size)
	{
		ft_print_hex(ptr[i + j], get_color(i + j));
		if (j % 2)
			write(1, " ", 1);
		j++;
	}
	while (j < 16)
	{
		write(1, "  ", 2);
		if (j % 2)
			write(1, " ", 1);
		j++;
	}
}

void		print_memory(const void *addr, size_t size)
{
	size_t			i;
	size_t			j;
	unsigned char	*ptr;

	i = 0;
	j = 0;
	ptr = (unsigned char*)addr;
	while (i < size)
	{
		j = 0;
		part_1(i, &j, size, ptr);
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_print_char(ptr[i + j], get_color(i + j));
			j++;
		}
		write(1, "\n", 1);
		i += 16;
	}
}
