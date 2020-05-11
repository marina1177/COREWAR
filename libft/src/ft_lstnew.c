/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:55:28 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/10 16:21:15 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	new = NULL;
	if ((new = (t_list*)malloc(sizeof(t_list))))
	{
		if (content != NULL)
		{
			new->content = (void*)malloc(sizeof(content));
			if (!(new->content))
				return (NULL);
			ft_memcpy((new->content), content, content_size);
			new->content_size = content_size;
		}
		else
		{
			new->content = NULL;
			new->content_size = 0;
		}
		new->next = NULL;
	}
	return (new);
}
