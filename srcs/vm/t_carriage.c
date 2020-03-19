/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_carriage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:06:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_carriage		*t_carriage_new(int num)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->num = num;
	new->prev = NULL;
	new->next = NULL;
	new->carry = false;
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
	list->size++;
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
	list->size++;
	return (new);
}

/*
** add to the front of list
*/
t_carriage		*t_carriages_push(t_carriages *list, t_carriage *new)
{
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		t_carriages_insert_before(list, list->head, new);
	}
	return (new);
}

t_carriage		*t_carriages_append(t_carriages *list, t_carriage *new)
{
	if (!list->tail)
		t_carriages_push(list, new);
	else
		t_carriages_insert_after(list, list->tail, new);
	return (new);
}
