#include "../../includes/vm.h"

static int	t_players_get_next_number(t_players *players)
{
	t_player	*temp;
	int			i;

	i = 1;
	temp = players->first_player;
	while (temp->next)
	{
		if (temp->num == i)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	t_players_set_num(t_players *players)
{
	t_player	*curr;
	t_player	*temp;

	curr = players->first_player;
	while (curr->next)
	{
		if (!curr->num)
			curr->num = t_players_get_next_number(players);
		curr = curr->next;
	}
}

int				t_players_is_sorted_desc(t_players *players)
{
	t_player	*curr;

	curr = players->first_player;
	while (curr->next)
	{
		if (curr->next->num > curr->num)
			return (0);
	}
	return (1);
}

void			t_players_sort_desc(t_players *players)
{
	t_player	*curr;
	t_player	*prev;

	while (!t_players_is_sorted_desc(players) && (curr = players->first_player))
	{		
		prev = players->first_player;
		while (curr->next)
		{
			if (curr->next->num > curr->num  && curr == players->first_player)
				{
					players->first_player = curr->next;
					curr->next = curr->next->next;
					players->first_player->next = curr;
					continue ;
				}
			else if (curr->next->num > curr->num)
			{
				prev->next = curr->next;
				curr->next = curr->next->next;			
				curr->next->next = curr;			
			}
			prev = curr;
			curr = curr->next;
		}
	}
}

/*
**	Create and insert new player in first position of Players` list
**	Return new player
*/
t_player *t_players_add_new_player(t_players *players, int number, t_vm *vm)
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
	new->qty = 0;
	new->first_player = NULL;
	new->last_alive = NULL;
	new->lives_num = -1;
	return (new);
}