# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include "../../includes/op.h"
# include "../../includes/vm.h"

static void		t_players_sort_desc(t_players *players)
{
	t_player	*curr;
	t_player	*prev;

	while (!t_players_is_sorted_desc(players) && (curr = players->first_player))
	{
		print_t_players(players);
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

int main(void)
{
		
}

/*
int main()
{
	t_dlist *carriages =  t_dlist_new();
	t_carriage *carr1 = t_carriage_new(1);
	t_carriage *carr2 = t_carriage_new(2);
	t_dlist_append(carriages, t_dlist_node_new(carr1));
	t_dlist_append(carriages, t_dlist_node_new(&carr2));
	
	printf("%d\n", ((t_carriage *)(carriages->head->data))->num);
	return (0);
}
*/
/*
int main(int ac, char **av)
{
	int a;
	int fd;
	char *buffer = (char *)malloc(sizeof(char) * 4);

	fd = open(av[1], O_RDONLY);
	read(fd, buffer, 4);

	a = (unsigned char)(buffer[0]) << 24 |
				(unsigned char)(buffer[1]) << 16 |
				(unsigned char)(buffer[2]) << 8 |
				(unsigned char)(buffer[3]);
	printf("%d", a == COREWAR_EXEC_MAGIC);
	return (0);
}
*/