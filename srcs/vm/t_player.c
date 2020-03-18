#include "../../includes/vm.h"

void	t_player_delete(t_player *prev, t_player *curr)
{
	prev ? prev->next = curr->next : 0;
	curr->name ? ft_free("1", curr->name) : 0;
	curr->comment ? ft_free("1", curr->comment) : 0;
	curr->code ? ft_free("1", curr->code) : 0;
	free(curr);		
}

static t_player *t_player_new(void)
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
	}
	return (new);
}

t_player *t_player_create(int number, t_vm *vm)
{
	t_player	*new;

	if (!(new = t_player_new()))
		handle_error_vm("Malloc", vm);
	new->num = number;
	return (new);
}