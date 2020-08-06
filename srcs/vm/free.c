/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:17:24 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 12:48:43 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		t_player_free(t_player **player)
{
	if (*player)
	{
		free((*player)->name);
		free((*player)->comment);
		free((*player)->code);
		free(*player);
	}
}

static int		t_players_free(t_vm *vm)
{
	t_player	*player;
	t_player	*temp;

	temp = vm->players->first_player;
	while (temp)
	{
		player = temp;
		temp = temp->next;
		t_player_free(&player);
	}
	free(vm->players);
	return (1);
}

static int		t_carriages_free(t_vm *vm)
{
	t_carriage	*carr;
	t_carriage	*temp;

	temp = vm->carr->head;
	while (temp)
	{
		carr = temp;
		temp = temp->next;
		free(carr);
	}
	free(vm->carr);
	return (1);
}

static int		t_cells_free(t_vm *vm)
{
	t_cells		*cell;
	t_cells		*temp;

	temp = vm->cells;
	while (temp)
	{
		cell = temp;
		temp = temp->next;
		free(cell);
	}
	return (1);
}

void			t_vm_free(t_vm *vm)
{
	vm->allocated & ALLOCATED_PLAYERS ? t_players_free(vm) : 0;
	vm->allocated & ALLOCATED_DATA ? ft_free("1", vm->data) : 0;
	vm->allocated & ALLOCATED_CARR ? t_carriages_free(vm) : 0;
	vm->allocated & ALLOCATED_MODS ? ft_free("1", vm->mods) : 0;
	vm->allocated & ALLOCATED_VS ? ft_free("1", vm->vs) : 0;
	vm->allocated & ALLOCATED_CELLS ? t_cells_free(vm) : 0;
	free(vm);
}
