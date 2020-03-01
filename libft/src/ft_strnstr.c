/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:37:38 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/01 16:00:57 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (len < ft_strlen(needle) && len > ft_strlen(haystack))
		return (NULL);
	if ((ft_strlen(needle) == 0))
		return ((char *)haystack);
	j = 0;
	while (haystack[j] != '\0' && j < len)
	{
		i = 0;
		while ((haystack[j + i] == needle[i] || !(needle[i])) && j + i <= len)
		{
			if (needle[i] == '\0')
				return ((char *)(haystack + j));
			i++;
		}
		j++;
	}
	return (NULL);
}
