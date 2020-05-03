/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		print_introduction(t_players *players)
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

void		print_final_result(t_vm *vm)
{
	t_player *winner;
	t_player *temp;
	
	temp = vm->players->first_player;
	winner = vm->players->first_player;
	while (temp)
	{
		if (winner->last_live < temp->last_live)
			winner = temp;
		temp = temp->next;
	}	
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->num, winner->name);
	exit(0);
}

void	print_last_alive(t_vm *vm)
{
	t_player *last;

	last = get_player_by_number(vm->players, vm->players->last_alive_num);
	ft_printf("Contestant %d, \"%s\", has won !\n",
				last->num, last->name);
	exit(0);
}

int		print_is_alive(int num, char *player_name)
{
	ft_printf("Player %d (%s) is said to be alive\n",
		num, player_name);
	return (1);
}




int		print_dump(t_vm *vm, int dump_size)
{	
	int		i;
	int		j;
	uint8_t	*arena;

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

/*
static void	vm_print_v_16(t_process p)
{
	int i;
	int	size;

	if (p.op.opcode != 0 && (p.op.opcode != 9 || !p.carry))
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
			p.pc_next - p.pc,
			p.offset + p.pc,
			p.offset + p.pc_next);
		i = p.offset + p.pc;
		size = 0;
		while (size < p.pc_next - p.pc)
		{
			if (i == MEM_SIZE)
				i = 0;
			ft_printf("%02x ", g_memory[i]);
			i++;
			size++;
		}
		ft_printf("\n");
	}
}
*/