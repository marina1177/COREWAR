/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_carriages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:05:39 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:07:43 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_carriages			*t_carriages_new(void)
{
	t_carriages		*new;

	new = (t_carriages *)malloc(sizeof(t_carriages));
	new->qty = 0;
	new->nums = 0;
	new->head = NULL;
	new->tail = NULL;
	return (new);
}

t_carriage	*t_carriages_pop(t_carriages *list, t_carriage *node)
{
	if (!node->prev)
		list->head = node->next;
	else
		node->prev->next = node->next;
	if (!node->next)
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

t_carriages			*t_carriages_remove_node(t_carriages *list, t_carriage *node)
{
	t_carriages_pop(list, node);
	free(node);
	return (list);
}

/*
** add to front of the list
*/
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

/*
** add to end of the list
*/
t_carriage		*t_carriages_append(t_carriages *list, t_carriage *new)
{
	if (!list->tail)
		t_carriages_push(list, new);
	else
		t_carriages_insert_after(list, list->tail, new);
	return (new);
}