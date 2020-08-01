/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_carriage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 11:18:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_carriage		*t_carriage_new(t_carriages *carr, int pos)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->num = carr->nums + 1;
	new->init_player = new->num;
	new->prev = NULL;
	new->next = NULL;
	new->carry = 0;
	new->pos = pos;
	new->op_code = 0;
	new->cycles_countdown = -1;
	new->last_cycle_alive = -1;
	ft_bzero((void *)new->regs, (REG_NUMBER + 1) * sizeof(int));
	new->regs[1] = -(new->num);
	return (new);
}

/*
** Add new node and set it to go the given pointer
*/

t_carriage		*t_carriages_insert_after(t_carriages *list,
t_carriage *node, t_carriage *new)
{
	new->prev = node;
	if (!node->next)
		list->tail = new;
	else
	{
		new->next = node->next;
		node->next->prev = new;
	}
	node->next = new;
	list->qty++;
	list->nums++;
	return (new);
}

t_carriage		*t_carriages_insert_before(t_carriages *list,
t_carriage *node, t_carriage *new)
{
	new->next = node;
	if (!node->prev)
		list->head = new;
	else
	{
		new->prev = node->prev;
		node->prev->next = new;
	}
	node->prev = new;
	list->qty++;
	list->nums++;
	return (new);
}

t_carriage		*t_carriage_copy(t_carriages *carr, t_carriage *src)
{
	t_carriage	*copy;
	int			i;

	copy = t_carriage_new(carr, src->pos);
	copy->carry = src->carry;
	copy->op_code = src->op_code;
	copy->pos = src->pos;
	copy->last_cycle_alive = src->last_cycle_alive;
	copy->init_player = src->init_player;
	i = -1;
	while (++i < REG_NUMBER + 1)
		copy->regs[i] = src->regs[i];
	return (copy);
}
