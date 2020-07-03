/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/07/03 15:14:36 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void			t_player_delete(t_player *prev, t_player *curr)
{
	prev ? prev->next = curr->next : 0;
	curr->name ? ft_free("1", curr->name) : 0;
	curr->comment ? ft_free("1", curr->comment) : 0;
	curr->code ? ft_free("1", curr->code) : 0;
	free(curr);
}

static t_player	*t_player_new(void)
{
	t_player	*new;

	new = (t_player *)malloc(sizeof(t_player));
	if (new)
	{
		new->num = 0;
		new->code_size = -1;
		new->name = NULL;
		new->comment = NULL;
		new->code = NULL;
		new->next = NULL;
		new->last_live = 0;
		new->is_alive = 1;
		new->start_code = -1;
		new->lives_in_period = 0;
	}
	return (new);
}

t_player		*t_player_create(int number, t_vm *vm)
{
	t_player	*new;

	if (!(new = t_player_new()))
		handle_error_vm("Malloc", vm);
	new->num = number;
	return (new);
}

t_player		*get_player_by_number(t_players *players, int num)
{
	t_player	*player;

	player = players->first_player;
	while (player)
	{
		if (player->num == num)
			return (player);
		player = player->next;
	}
	return (player);
}
