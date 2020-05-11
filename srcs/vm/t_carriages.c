/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_carriages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:05:39 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:15:34 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_carriage		*t_carriages_pop(t_carriages *list, t_carriage *node)
{
	if (node->prev == NULL)
	{
		list->head = node->next;
	}
	else
	{
		node->prev->next = node->next;
	}
	if (node->next == NULL)
		list->tail = node->prev;
	else
		node->next->prev = node->prev;
	if (node->next == node && node->prev == node)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	list->qty--;
	return (node);
}

t_carriages		*t_carriages_remove_node(t_carriages *list, t_carriage *node)
{
	t_carriages_pop(list, node);
	free(node);
	node = NULL;
	return (list);
}

t_carriage		*t_carriages_push(t_carriages *list, t_carriage *new)
{
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
		list->nums++;
		list->qty++;
	}
	else
	{
		t_carriages_insert_before(list, list->head, new);
	}
	return (new);
}

t_carriages		*t_carriages_create(t_vm *vm)
{
	t_carriages	*new;

	new = (t_carriages *)malloc(sizeof(t_carriages));
	if (!new)
		handle_error_vm(ERR_ALLOC, vm);
	new->qty = 0;
	new->nums = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}
