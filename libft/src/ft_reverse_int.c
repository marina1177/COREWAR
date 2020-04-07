/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:50:32 by bcharity          #+#    #+#             */
/*   Updated: 2019/11/02 16:50:57 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse(int *arr, int dist, size_t size)
{
	int	tmp[dist];
	int	*p;
	int	i;

	if (dist > (int)size)
		return ;
	i = -1;
	p = arr + dist - 1;
	while (i++ < dist)
	{
		tmp[i] = *p;
		p--;
	}
	ft_memcpy(arr, tmp, dist * sizeof(int));
}
