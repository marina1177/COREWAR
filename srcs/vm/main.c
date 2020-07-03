/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/07/03 16:46:51 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		delete_old_carriages(t_vm *vm)
{
	t_carriage	*curr;
	t_carriage	*temp;

	curr = vm->carr->head;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		if (vm->data->cycles_to_die <= 0 ||
		vm->data->cycles - temp->last_cycle_alive >= vm->data->cycles_to_die)
		{
			if (vm->mods->verb_lvl & VERB_L4)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				temp->num,
				vm->data->cycles - temp->last_cycle_alive,
				vm->data->cycles_to_die);
			t_carriages_remove_node(vm->carr, temp);
			vs_state_refresh(vm);
		}
	}
}

static void		check_carriages(t_vm *vm)
{
	delete_old_carriages(vm);
	t_players_check_is_alive(vm, vm->players);
	vm->data->checks_counter++;
	if (vm->data->lives_counter >= NBR_LIVE ||
		vm->data->checks_counter == MAX_CHECKS)
	{
		vm->data->cycles_to_die -= CYCLE_DELTA;
		vm->data->checks_counter = 0;
		if (vm->mods->verb_lvl & VERB_L2)
			ft_printf("Cycle to die is now %d\n", vm->data->cycles_to_die);
		t_players_reset_lives_in_period(vm->players);
	}
	vm->data->lives_counter = 0;
	vs_state_refresh(vm);
}

void			corewar(t_vm *vm)
{
	int			cycles;

	cycles = 0;
	while (vm->carr->qty)
	{
		if (vm->data->cycles && (vm->mods->verb_lvl & VERB_L2))
			ft_printf("It is now cycle %d\n", vm->data->cycles);
		handle_carriages(vm);
		if (vm->mods->dump_cycle == vm->data->cycles)
		{
			print_dump(vm, vm->mods->dump_size);
		}
		if (cycles == vm->data->cycles_to_die || vm->data->cycles_to_die <= 0)
		{
			check_carriages(vm);
			cycles = 0;
		}
		vm->data->cycles++;
		cycles++;
		print_vsconst(vm, 1);
	}
}

void			create_arena(t_vm *vm)
{
	t_player	*player;
	int			diff;
	int			i;
	int			j;

	diff = MEM_SIZE / vm->players->qty;
	player = vm->players->first_player;
	i = 0;
	while (player)
	{
		ft_memcpy((char *)((vm->data->arena) + i),
				player->code, player->code_size);
		player->start_code = i;
		t_carriages_push(vm->carr, t_carriage_new(vm->carr, i));
		new_cells(&(vm->cells), player->num, vm);
		j = i - 1;
		while (++j < i + player->code_size)
			push_cells(vm, player->num, j);
		i += diff;
		player = player->next;
	}
	vm->players->last_alive_num = vm->players->qty;
}

int				main(int ac, char **av)
{
	t_vm		*vm;

	ac < 2 ? print_usage() : 0;
	vm = t_vm_create();
	parse_args(vm, ac, av);
	print_introduction(vm->players);	
	create_arena(vm);
	print_vsconst(vm, 0);	
	corewar(vm);	
	print_final_result(vm);
	return (0);
}
