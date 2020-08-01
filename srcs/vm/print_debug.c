/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/08/01 12:50:15 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void			print_t_player(t_player *player)
{
	ft_printf("Player num %-4d, ", player->num);
	ft_printf("name %-15s\n", player->name);
}

void			print_t_players(t_players *players)
{
	t_player	*temp;

	temp = players->first_player;
	ft_printf("Players qty %-4d\n", players->qty);
	while (temp)
	{
		print_t_player(temp);
		temp = temp->next;
	}
}

void			print_int_arr_in_row(int *arr, int size)
{
	int			i;

	i = 0;
	while (++i < size)
		ft_printf("%d ", arr[i]);
	ft_putchar('\n');
}

void			print_t_carriage(t_carriage *carriage)
{
	ft_printf("Number %-4d, position 0x%04x\n", carriage->num, carriage->pos);
	ft_printf("opcode %-4d, countdown %-8d\n", carriage->op_code,
			carriage->cycles_countdown);
	print_int_arr_in_row(carriage->regs, REG_NUMBER + 1);
	ft_putchar('\n');
}

void			print_t_carriages(t_vm *vm)
{
	t_carriage	*carriage;

	if (!vm->mods->pc)
		return ;
	if (vm->mods->dump_cycle > -1 && vm->mods->dump_cycle != vm->data->cycles)
		return ;
	carriage = vm->carr->head;
	ft_printf("%s== START t_carriages_print. CYCLE: %7d ==\n%s",
	C_GRN, vm->data->cycles, C_NRM);
	while (carriage)
	{
		print_t_carriage(carriage);
		carriage = carriage->next;
	}
	ft_printf("%s== END t_carriages_print ==\n%s", C_GRN, C_NRM);
	ft_printf("=============================================\n");
}
