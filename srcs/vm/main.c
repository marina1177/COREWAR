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
		i += diff;
		player = player->next;
	}	
}

void	game(t_vm *vm, t_players *players, t_carriages *carr)
{
	int	i;

	i = 0;
	while (carr->qty)
	{
		vm->mods->dump_cycle == vm->data->cycles && print_dump(vm) ? exit(0) : 0;
		if (i == vm->data->cycles_to_die || vm->data->cycles_to_die <=0)
		{
			check(vm);
			i = 0;
		}
		vm->data->cycles++;
		i++;			
	}
	print_final_result(vm);
}

int     main(int ac, char **av)
{
	t_vm	*vm;

	ac < 2 ? print_usage() : 0;	
	vm = t_vm_create();
	parse_args(vm, ac, av);
	//print_introduction(vm->players);
	//print_t_players(vm->players);
	create_arena(vm);
	//print_t_carriages(vm->carr);
	//print_dump(vm->data->arena, 64);
	game(vm, vm->players, vm->carr);
	return (0);
}