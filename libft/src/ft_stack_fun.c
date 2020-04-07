/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:46:44 by bcharity          #+#    #+#             */
/*   Updated: 2019/11/02 15:50:49 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack		*ft_stack_create(size_t stack_size)
{
	t_stack	*new;

	if (!(new = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	if (!(new->arr = (int *)malloc(stack_size * sizeof(int))))
	{
		free(new);
		return (NULL);
	}
	new->capacity = stack_size;
	new->itop = stack_size - 1;
	return (new);
}

t_stack		*ft_stack_push(t_stack *st, int val)
{
	if (st->itop == 0)
		return (st);
	st->arr[st->itop--] = val;
	return (st);
}

int			ft_stack_pop(t_stack *src, t_stack *dst, size_t n)
{
	size_t	tmp;

	if (n > (tmp = dst->itop))
		n = tmp;
	if (n > (tmp = src->capacity - src->itop))
		n = tmp;
	while (n--)
	{
		dst->arr[dst->itop--] = src->arr[++src->itop];
	}
	return (0);
}

void		ft_stack_swap(t_stack *st)
{
	int	tmp;

	tmp = st->arr[st->itop];
	st->arr[st->itop] = st->arr[st->itop + 1];
	st->arr[st->itop + 1] = tmp;
}
