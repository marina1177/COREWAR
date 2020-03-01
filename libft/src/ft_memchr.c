/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:30:40 by bcharity          #+#    #+#             */
/*   Updated: 2019/04/20 10:05:54 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dst, int c, size_t n)
{
	size_t					i;
	const unsigned char		*d;

	i = 0;
	d = (const unsigned char *)dst;
	while (i < n)
	{
		if (d[i] == (unsigned char)c)
			return ((void*)(dst + i));
		i++;
	}
	return (NULL);
}
