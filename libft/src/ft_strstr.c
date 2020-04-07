/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:36:40 by bcharity          #+#    #+#             */
/*   Updated: 2020/02/29 17:22:00 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *ph;
	const char *pn;

	pn = needle;
	while (haystack)
	{
		ph = haystack;
		while (*(haystack) == *(needle) || !(*needle))
		{
			if (!(*needle))
			{
				return ((char*)ph);
			}
			haystack++;
			needle++;
		}
		if (!*haystack)
			return (NULL);
		needle = pn;
		haystack = ph + 1;
	}
	return (NULL);
}
