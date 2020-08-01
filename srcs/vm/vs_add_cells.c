/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_add_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:17:30 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 17:19:19 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_cells			*new_cells(t_cells **head, int id, t_vm *vm)
{
	t_cells	*new;
	t_cells	*p;

	if (!(new = (t_cells*)malloc(sizeof(t_cells))))
		handle_error_vm(ERR_ALLOC, vm);
	if (!(vm->allocated & ALLOCATED_CELLS))
		vm->allocated += ALLOCATED_CELLS;
	new->next = NULL;
	new->num_addr = -1;
	new->players_id = id;
	if (*head == NULL)
		*head = new;
	else
	{
		p = *head;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
	return (new);
}

t_cells			*find_id(t_cells **head, int id, t_vm *vm)
{
	t_cells	*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->players_id == id)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (new_cells(head, id, vm));
}

void			push_cells(t_vm *vm, int player_id, int cell_number)
{
	t_cells		*cells;

	cells = find_id(&(vm->cells), player_id, vm);
	cells->num_addr++;
	cells->cells_address[cells->num_addr] = cell_number;
	vs_cells_refresh(vm);
}

void			vs_push_cells(t_vm *vm,
			int cell_number, t_carriage *carriage)
{
	if (vm->mods->vs)
	{
		push_cells(vm, carriage->init_player, cell_number);
	}
}
