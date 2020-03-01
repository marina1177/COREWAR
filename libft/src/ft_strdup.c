/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 09:13:29 by bcharity          #+#    #+#             */
/*   Updated: 2019/04/27 14:33:32 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*buf;

	buf = NULL;
	len = 0;
	while (src[len])
	{
		len++;
	}
	buf = (char*)malloc((sizeof(char) * (len + 1)));
	if (buf != NULL)
	{
		i = 0;
		while (i < len)
		{
			buf[i] = src[i];
			i++;
		}
		buf[i] = '\0';
		return (buf);
	}
	return (NULL);
}
