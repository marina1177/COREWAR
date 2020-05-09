#include "../../includes/vm.h"

static int		t_players_is_sorted_desc(t_players *players)
{
	t_player	*curr;

	curr = players->first_player;
	while (curr->next)
	{
		if (curr->next->num < curr->num)
			return (0);
		curr = curr->next;		
	}
	return (1);
}

static void		sort_desc_traverse_cycle(t_player *curr,
				t_player *prev, t_players *players)
{
	while (!t_players_is_sorted_desc(players) && (curr = players->first_player))
	{		
		prev = players->first_player;
		while (curr && curr->next)
		{
			if (curr->next->num < curr->num  && curr == players->first_player)
				{
					players->first_player = curr->next;
					curr->next = curr->next->next;
					players->first_player->next = curr;
					prev = players->first_player;
					continue ;
				}
			else if (curr->next->num < curr->num)
			{
				prev->next = curr->next;
				curr->next = curr->next->next;
				prev->next->next = curr;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}

static void		t_players_sort_desc(t_players *players)
{
	t_player	*curr;
	t_player	*prev;

	curr = NULL;
	prev = NULL;
	sort_desc_traverse_cycle(curr, prev, players);	
}

static void		t_players_set_num(t_players *players)
{
	t_player	*curr;

	curr = players->first_player;
	while (curr)
	{
		if (!curr->num)
			curr->num = t_players_get_next_number(players);
		curr = curr->next;		
	}	
}

void			handle_players(t_vm *vm, t_players *players)
{
	t_player	*temp;

	if (players->qty > MAX_PLAYERS)
		handle_error_int_arg(ERR_MAX_PLAYERS, MAX_PLAYERS, vm);
	t_players_set_num(players);
	t_players_sort_desc(players);
	temp = players->first_player;
	while (temp)
	{
		if (temp->num > players->qty)
			handle_error_str_arg(ERR_INV_P_NUM, temp->name, vm);
		temp = temp->next;
	}
	vm->players->last_alive_num = players->first_player->num;
}
