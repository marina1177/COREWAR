/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_players.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 21:56:47 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int				t_players_get_next_number(t_players *players)
{
	t_player	*temp;
	int			i;

	i = 1;
	temp = players->first_player;
	while (temp)
	{
		if (temp->num == i)
		{
			i++;
			temp = players->first_player;
		}
		else
			temp = temp->next;
	}
	return (i);
}

t_player		*t_players_add(t_players *players, int number, t_vm *vm)
{
	t_player	*new;

	new = t_player_create(number, vm);
	if (!players->first_player)
	{
		players->first_player = new;
		players->last_player = new;
	}
	else
	{
		players->last_player->next = new;
		players->last_player = new;
	}
	players->qty++;
	return (new);
}

t_players		*t_players_new(void)
{
	t_players	*new;

	new = (t_players *)malloc(sizeof(t_players));
	if (new)
	{
		new->qty = 0;
		new->first_player = NULL;
		new->last_player = NULL;
		new->last_alive_num = 0;
		new->lives_num = -1;
	}
	return (new);
}

void			t_players_reset_lives_in_period(t_players *players)
{
	t_player	*temp;

	temp = players->first_player;
	while (temp)
	{
		temp->lives_in_period = 0;
		temp = temp->next;
	}
}
