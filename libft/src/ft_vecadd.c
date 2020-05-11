/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzei <wzei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:53:03 by wzei              #+#    #+#             */
/*   Updated: 2019/09/25 06:24:24 by wzei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vecadd(t_vector *v, void *e)
{
	void	*tmp;

	if (v->size == 0)
	{
		v->size = 10;
		v->data = malloc(sizeof(void *) * v->size);
		ft_bzero(v->data, sizeof(void) * v->size);
	}
	if (v->size == v->count)
	{
		v->size *= 2;
		tmp = malloc(sizeof(void *) * v->size);
		ft_bzero(tmp, sizeof(void) * v->size);
		ft_memcpy(tmp, v->data, sizeof(void *) * v->count);
		free(v->data);
		v->data = tmp;
	}
	v->data[v->count] = e;
	v->count++;
}
