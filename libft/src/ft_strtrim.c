/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:27:48 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/01 11:12:50 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*trim;
	size_t	start;
	size_t	stop;

	start = 0;
	if (!s)
		return (NULL);
	stop = ft_strlen(s) - 1;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	if (s[start] == '\0')
	{
		trim = ft_strsub(s, start, 1);
		return (trim);
	}
	while (s[stop] == ' ' || s[stop] == '\t' || s[stop] == '\n')
		stop--;
	trim = ft_strsub(s, start, (stop - start + 1));
	return (trim);
}
