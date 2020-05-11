/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzei <wzei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:55:33 by wzei              #+#    #+#             */
/*   Updated: 2019/03/12 04:27:43 by wzei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vecdel(t_vector *v, int index)
{
	int		i;
	int		j;
	void	**newarr;

	if (v)
	{
		if (index >= v->count)
			return ;
		v->data[index] = NULL;
		newarr = (void **)malloc(sizeof(void *) * v->count * 2);
		i = 0;
		j = 0;
		while (i < v->count)
		{
			if (v->data[i] != NULL)
			{
				newarr[j] = v->data[i];
				j++;
			}
			i++;
		}
		free(v->data);
		v->data = newarr;
		v->count--;
	}
}
