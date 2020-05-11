/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzei <wzei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:50:01 by wzei              #+#    #+#             */
/*   Updated: 2019/09/25 08:00:03 by wzei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*ft_vecnew(void)
{
	t_vector	*ret;

	ret = (t_vector *)malloc(sizeof(t_vector));
	if (ret)
	{
		ret->data = NULL;
		ret->size = 0;
		ret->count = 0;
	}
	return (ret);
}
