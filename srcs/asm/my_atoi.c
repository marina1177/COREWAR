/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:33:27 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 16:48:42 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

static void			error_atoi(void)
{
	char	*s;

	s = "Error atoi\n";
	write(2, s, ft_strlen(s));
	free_data();
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
		error_atoi();
	}
	if (i > 18 && n == -1)
	{
		error_atoi();
	}
	return (1);
}

int					my_atoi(const char *str)
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
			error_atoi();
	}
	check_valid(str, n);
	while (*str >= 48 && *str <= 57)
	{
		val = 10 * val + (*str - 48);
		str++;
	}
	if (n * val < -2147483648
		|| n * val > 2147483647)
		error_atoi();
	return (n * (int)val);
}
