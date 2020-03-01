/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:36:28 by bcharity          #+#    #+#             */
/*   Updated: 2019/04/20 13:54:53 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *mp1, const void *mp2, size_t n)
{
	unsigned char	s1;
	unsigned char	s2;

	while (n--)
	{
		s1 = *(unsigned char*)mp1;
		s2 = *(unsigned char*)mp2;
		if (s1 != s2)
			return (s1 - s2);
		mp1++;
		mp2++;
	}
	return (0);
}
