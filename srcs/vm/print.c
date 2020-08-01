/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/08/01 11:17:28 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void			print_introduction(t_players *players)
{
	int			i;
	t_player	*temp;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < players->qty)
	{
		temp = players->first_player;
		while (temp)
		{
			if (temp->num == i + 1)
				ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
						temp->num, temp->code_size, temp->name, temp->comment);
			temp = temp->next;
		}
	}
}

void			print_final_result(t_vm *vm)
{
	t_player	*winner;

	winner = get_player_by_number(vm->players, vm->players->last_alive_num);
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->num,
		winner->name);
	print_vsconst(vm, 2);
	exit(0);
}

int				print_is_alive(int num, char *player_name)
{
	ft_printf("Player %d (%s) is said to be alive\n",
		num, player_name);
	return (1);
}

int				print_dump(t_vm *vm, int dump_size)
{
	int			i;
	int			j;
	uint8_t		*arena;

	arena = vm->data->arena;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < dump_size)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += dump_size;
	}
	exit(0);
	return (1);
}

void			print_move(t_vm *vm, t_carriage *carriage, int temp_pos)
{
	int			i;
	int			size;
	int			diff;

	if (!(vm->mods->verb_lvl & VERB_L5))
		return ;
	if (carriage->op_code != 0 && (carriage->op_code != 9 || !carriage->carry))
	{
		if ((diff = norm_pos(carriage->pos - temp_pos)) <= 1)
			return ;
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", diff, temp_pos,
			temp_pos + diff);
		i = temp_pos;
		size = 0;
		while (size < norm_pos(carriage->pos - temp_pos))
		{
			if (i == MEM_SIZE)
				i = 0;
			ft_printf("%02x ", vm->data->arena[i]);
			i++;
			size++;
		}
		ft_printf("\n");
	}
}
