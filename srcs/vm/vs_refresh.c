#include "../../includes/vm.h"

//??? ¯\_(ツ)_/¯????

void	state_refresh(t_vm *vm)
{
	vm->vs->state_refresh += 1;
}

void	players_refresh(t_vm *vm)
{
	vm->vs->players_refresh += 1;
}

void	carriages_refresh(t_vm *vm)
{
	vm->vs->carriages_refresh += 1;
}

void	cells_refresh(t_vm *vm)
{
	vm->vs->cells_refresh += 1;
}
