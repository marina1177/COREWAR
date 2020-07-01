/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:17:24 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:17:25 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		ft_exit(char *line)
{
	ft_printf("%s", line);
	exit(0);
}

int			is_integer(char *s)
{
	size_t	len;
	int		n;

	n = ft_atoi(s);
	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || (int)len != ft_ilen(n))
		return (0);
	if (s[0] == '-' && len == 1)
		return (0);
	return (1);
}

void		t_players_check_is_alive(t_vm *vm, t_players *players)
{
	t_player	*temp;

	temp = players->first_player;
	while (temp)
	{
		if (vm->data->cycles_to_die <= 0 ||
		vm->data->cycles - temp->last_live >= vm->data->cycles_to_die)
		{
			temp->is_alive = 0;
			vs_players_refresh(vm);
		}
		temp = temp->next;
	}
}

static void	t_player_free(t_player **player)
{
	if (*player)
	{
		free((*player)->name);
		free((*player)->comment);
		free((*player)->code);
		free(*player);
	}	
}

static int	t_players_free(t_vm *vm)
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

static int	t_carriages_free(t_vm *vm)
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

static int	t_cells_free(t_vm *vm)
{
	t_cells	*cell;
	t_cells	*temp;
	
	temp = vm->cells;
	while (temp)
	{
		cell = temp;
		temp = temp->next;
		free(cell);		
	}	
	return (1);
}

void		t_vm_free(t_vm *vm)
{
	vm->allocated & ALLOCATED_PLAYERS ? t_players_free(vm) : 0;
	vm->allocated & ALLOCATED_DATA ? ft_free("1", vm->data) : 0;
	vm->allocated & ALLOCATED_CARR ? t_carriages_free(vm) : 0;
	vm->allocated & ALLOCATED_MODS ? ft_free("1", vm->mods) : 0;
	vm->allocated & ALLOCATED_CELLS ? t_cells_free(vm) : 0;
}

int			norm_pos(int pos)
{
	if (pos < 0)
		pos += MEM_SIZE;
	else if (pos >= MEM_SIZE)
		pos %= MEM_SIZE;
	return (pos);
}