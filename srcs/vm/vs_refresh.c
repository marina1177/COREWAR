#include "../../includes/vm.h"

int		vs_state_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->state_refresh = 1;
	return (1);	
}

int		vs_players_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->players_refresh = 1;
	return (1);	
}

int		vs_carriages_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->carriages_refresh = 1;
	return (1);
}

int		vs_cells_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->cells_refresh = 1;
	return (1);
}

int		vs_reset_refresh(t_vm *vm)
{
	t_cells *temp;

	if (vm->mods->vs)
	{
		temp = vm->cells;
		while (temp)
		{
			temp->num_addr = -1;
			temp = temp->next;
		}		
		vm->vs->cells_refresh = 0;
		vm->vs->carriages_refresh = 0;
		vm->vs->players_refresh = 0;
		vm->vs->state_refresh = 0;
	}
	return (1);
}