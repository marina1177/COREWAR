/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:20:08 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/04 09:24:31 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*freemem(char **split, size_t i)
{
	while (i > 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static size_t		count_word(char const *s, char c)
{
	char	*p;
	size_t	lns;

	if (!s)
		return (0);
	lns = 0;
	p = (char*)s;
	while (*p != '\0')
	{
		if (*p != c && (*(p + 1) == c || *(p + 1) == '\0'))
			lns++;
		p++;
	}
	return (lns);
}

static size_t		count_ch(char const *s, char c)
{
	size_t ch;

	ch = 0;
	while (*s != c && *s != '\0')
	{
		ch++;
		s++;
	}
	s--;
	return (ch);
}

static void			fillmem(char const *s, char c, size_t i, char **split)
{
	size_t	ch;

	ch = count_ch(s, c);
	if ((split[i] = (char*)malloc((ch + 1) * sizeof(char*))))
	{
		ft_memcpy(split[i], s, ch);
		split[i][ch] = '\0';
	}
	else
		freemem(split, i);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s ||
			!(split = (char**)malloc(((count_word(s, c)) + 1) * sizeof(char*))))
		return (NULL);
	else if (*s && s)
	{
		while (i < (count_word(s, c)) && s[j] != '\0')
		{
			if ((s[j] != c && ((s[j - 1]) == c || (s[j + 1]) == '\0'))
					|| (j == 0 && s[j] != c))
			{
				fillmem(&(s[j]), c, i, split);
				i++;
				j++;
			}
			j++;
		}
	}
	split[count_word(s, c)] = NULL;
	return (split);
}
