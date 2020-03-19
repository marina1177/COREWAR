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
		ft_memcpy((char *)((vm->data->arena) + i), player->code, player->code_size);
		i += diff;
		player = player->next;
	}	
}

int     main(int ac, char **av)
{
	t_vm	*vm;

	ac < 2 ? print_usage() : 0;	
	vm = t_vm_create();
	parse_args(vm, ac, av);
	print_t_players(vm->players);
	create_arena(vm);
	print_dump(vm->data->arena, 64);
	return (0);
}