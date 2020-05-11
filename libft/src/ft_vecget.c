/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzei <wzei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:54:51 by wzei              #+#    #+#             */
/*   Updated: 2019/03/12 04:08:38 by wzei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vecget(t_vector *v, int index)
{
	if (v)
	{
		if (index >= v->count)
			return (NULL);
		return (v->data[index]);
	}
	return (NULL);
}
