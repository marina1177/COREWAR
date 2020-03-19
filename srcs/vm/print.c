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

void		print_intro(t_players *players)
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
						temp->code_size, temp->name, temp->comment);
			temp = temp->next;
		}
	}
}

void	print_last_alive(t_vm *vm)
{
	t_player *last;

	last = vm->players->last_alive;
	ft_printf("Contestant %d, \"%s\", has won !\n",
				last->num, last->name);
}

void		print_dump(uint8_t *arena, int print_mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < print_mode)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += print_mode;
	}
}