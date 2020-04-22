/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_t_player(t_player *player)
{
	ft_printf("Player num %-4d, ", player->num);
	ft_printf("name %-15s\n", player->name);	
}

void	print_t_players(t_players *players)
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

void	print_int_arr_in_row(int *arr, int size)
{
	int	i;

	i = 0;
	while (++i < size)	
		ft_printf("%d ", arr[i]);
	ft_putchar('\n');
}

void	print_t_carriage(t_carriage *carriage)
{	
	ft_printf("Number %-4d, position %-8d\n", carriage->num, carriage->pos);
	ft_printf("opcode %-4d, countdown %-8d\n", carriage->op_code, carriage->cycles_countdown);
	print_int_arr_in_row(carriage->regs, REG_NUMBER + 1);
	ft_putchar('\n');
}

void	print_t_carriages(t_carriages *carriages)
{
	t_carriage *carr;

	carr = carriages->head;
	ft_printf("======== t_carriages_print ========\n");
	while (carr)
	{
		print_t_carriage(carr);
		carr = carr->next;
	}
	ft_printf("======== END t_carriages_print ====\n");
}