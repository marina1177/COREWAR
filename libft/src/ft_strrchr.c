/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 09:26:03 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/09 11:06:00 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if ((char)str[len] == (char)ch)
			return ((char*)&(str[len]));
		len--;
	}
	return (NULL);
}
