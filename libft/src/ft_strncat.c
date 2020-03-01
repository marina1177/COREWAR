/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:45:02 by bcharity          #+#    #+#             */
/*   Updated: 2019/04/20 14:33:02 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*tmp;
	size_t	ldst;
	size_t	lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	tmp = dst;
	if (lsrc < n)
	{
		ft_strcpy(&dst[ldst], src);
	}
	else
	{
		ft_strncpy(&dst[ldst], src, n);
		dst[ldst + n] = '\0';
	}
	return (tmp);
}
