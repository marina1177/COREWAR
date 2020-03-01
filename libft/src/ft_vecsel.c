/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecsel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzei <wzei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 03:05:33 by wzei              #+#    #+#             */
/*   Updated: 2019/03/12 03:05:41 by wzei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vecsel(t_vector *vec, size_t off, void *tst, size_t s)
{
	int		iter;
	int		col;
	void	*ret;

	if (!vec || !tst)
		return (NULL);
	iter = 0;
	ret = NULL;
	col = ft_veccnt(vec);
	while (iter < col)
	{
		ret = ft_vecget(vec, iter);
		if (ft_memcmp(ret + off, tst, s))
			ret = NULL;
		if (ret != NULL)
			break ;
		iter++;
	}
	return (ret);
}
