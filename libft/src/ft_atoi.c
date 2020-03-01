/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:53:25 by bcharity          #+#    #+#             */
/*   Updated: 2020/02/02 12:14:13 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			error(void)
{
	char	*s;

	s = "Error\n";
	write(2, s, ft_strlen(s));
	exit(0);
}

static int			check_valid(const char *s, int n)
{
	int			i;
	const char	*str;

	i = 0;
	str = s;
	while (*str >= 48 && *str <= 57)
	{
		i++;
		str++;
	}
	if (i > 18 && n == 1)
	{
		error();
	}
	if (i > 18 && n == -1)
	{
		error();
	}
	if ((*str < 48 || *str > 57) && *str != '\0')
	{
		error();
	}
	return (1);
}

int					ft_atoi(const char *str)
{
	int				n;
	long long int	val;

	val = 0;
	n = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		n = (*str == '-') ? -1 : 1;
		str++;
		if (*str == '\0')
			error();
	}
	check_valid(str, n);
	while (*str >= 48 && *str <= 57)
	{
		val = 10 * val + (*str - 48);
		str++;
	}
	if (n * val < -2147483648
		|| n * val > 2147483647)
		error();
	return (n * (int)val);
}
