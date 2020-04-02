#include "../../includes/vm.h"

t_carriage	*make_new_carriage(unsigned int position)
{
	t_carriage		*new;
	int i;

	i = -1;
	new = NULL;
	if (!(new = (t_carriage*)malloc(sizeof(t_carriage))))
		ft_exit(ERR_ALLOC);
	new->position = position;
	new->last_cycle_alive = 0;
	new->num_of_carriage = 0;
	new->carry = 0;
	while (++i <= REG_NUMBER)
		new->regs[i] = 0;
	new->next = NULL;
	return (new);
}

void	add_carriage(t_carriage **head, t_carriage *new)
{
	if (head && new)
	{
		new->next = *head;
		*head = new;
	}
	else
		*head = new;
}

void	del_carriage(t_carriage **head, t_carriage *carriage)
{
	t_carriage *p;

	if (*head && carriage)
	{
		//printf("%p - %p\n", *head, carriage);
		p = *head;
		while (p != carriage && p->next)
		{
			p = p->next;
		}
		*head = p->next;
		//printf("free %p\n", p);
		free(p);
	}
	else
		printf("проблема с очисткой кареток/n"); //delete
}