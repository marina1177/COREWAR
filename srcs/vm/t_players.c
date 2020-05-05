#include "../../includes/vm.h"

static int		t_players_get_next_number(t_players *players)
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

static int		t_players_is_sorted_desc(t_players *players)
{
	t_player	*curr;

	curr = players->first_player;
	while (curr->next)
	{
		if (curr->next->num > curr->num)
			return (0);
		curr = curr->next;		
	}
	return (1);
}

static void		t_players_sort_desc(t_players *players)
{
	t_player	*curr;
	t_player	*prev;

	while (!t_players_is_sorted_desc(players) && (curr = players->first_player))
	{		
		prev = players->first_player;
		while (curr && curr->next)
		{
			if (curr->next->num > curr->num  && curr == players->first_player)
				{
					players->first_player = curr->next;
					curr->next = curr->next->next;
					players->first_player->next = curr;
					prev = players->first_player;
					continue ;
				}
			else if (curr->next->num > curr->num)
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

/*
**	Create and insert new player in first position of Players` list
**	Return new player
*/
t_player *t_players_add(t_players *players, int number, t_vm *vm)
{
	t_player	*new;

	new = t_player_create(number, vm);
	new->next = players->first_player;
	players->first_player = new;
	players->qty++;
	return (new);
}

t_players *t_players_new(void)
{
	t_players	*new;

	new = (t_players *)malloc(sizeof(t_players));
	if (new)
	{
		new->qty = 0;
		new->first_player = NULL;
		new->last_alive_num = 0;
		new->lives_num = -1;
	}
	return (new);
}

t_player *get_player_by_number(t_players *players, int num)
{
	t_player *player;

	player = players->first_player;
	while (player)
	{
		if (player->num == num)
			return (player);
		player = player->next;
	}
	return (player);
}

void handle_players(t_vm *vm, t_players *players)
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