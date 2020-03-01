/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:24:53 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/01 14:47:32 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *buf;

	buf = NULL;
	buf = (void*)malloc(size);
	if (buf != NULL)
	{
		ft_memset(buf, '\0', size);
		return (buf);
	}
	else
		return (NULL);
}
