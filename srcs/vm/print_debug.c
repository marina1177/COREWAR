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
