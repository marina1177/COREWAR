/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:51:16 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/01 18:05:07 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*point;
	t_list	*new;

	point = f(lst);
	new = point;
	if (!lst || !f)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		if ((point->next = f(lst)) == NULL)
		{
			free(point->next);
			return (NULL);
		}
		point = point->next;
	}
	return (new);
}
