#include "../../includes/vm.h"

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