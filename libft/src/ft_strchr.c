/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:50:02 by bcharity          #+#    #+#             */
/*   Updated: 2020/03/28 14:01:42 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == (char)ch)
			return ((char*)(&str[i]));
		i++;
	}
	return (0);
}
