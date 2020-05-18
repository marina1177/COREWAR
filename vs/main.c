/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 18:04:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"



static void		delete_old_carriages(t_vm *vm)
{
	t_carriage *curr;

	curr = vm->carr->head;
	while (curr)
	{
		if (vm->data->cycles_to_die <= 0 ||
		vm->data->cycles - curr->last_cycle_alive >= vm->data->cycles_to_die)
			t_carriages_remove_node(vm->carr, curr);
		curr = curr->next;
	}
}

static void		check_carriages(t_vm *vm)
{
	delete_old_carriages(vm);
	vm->data->checks_counter++;
	if (vm->data->lives_counter > NBR_LIVE ||
		vm->data->checks_counter == MAX_CHECKS)
	{
		vm->data->cycles_to_die -= CYCLE_DELTA;
		vm->data->checks_counter = 0;
	}
	vm->data->lives_counter = 0;
}

void	corewar(t_vm *vm)
{
	int	cycles;

	cycles = 0;
	while (vm->carr->qty)
	{
		handle_carriages(vm);
		if (vm->mods->dump_cycle == vm->data->cycles)
			print_dump(vm, vm->mods->dump_size);
		if (cycles == vm->data->cycles_to_die || vm->data->cycles_to_die <=0)
		{
			check_carriages(vm);
			cycles = 0;
		}
		vm->data->cycles++;
		cycles++;
	}
}

void	create_arena(t_vm *vm)
{
	t_player	*player;
	int			diff;
	int			i;

	diff = MEM_SIZE / vm->players->qty;
	player = vm->players->first_player;
	i = 0;
	while (player)
	{
		ft_memcpy((char *)((vm->data->arena) + i),
				player->code, player->code_size);
		t_carriages_push(vm->carr, t_carriage_new(vm->carr, i));
		player->start_code = i;
		i += diff;
		player = player->next;
	}
}


int		main(int ac, char **av)
{
	t_vm	*vm;

	ac < 2 ? print_usage() : 0;
	vm = t_vm_create();
	parse_args(vm, ac, av);
	print_introduction(vm->players);
	create_arena(vm);
	if (vm->vs)
		print_vsconst(vm, 0);//start
	corewar(vm);
	printf("main_ERROR_CODE = %d\n", vm->vs->error_code);

	print_final_result(vm);
	return (0);
}
