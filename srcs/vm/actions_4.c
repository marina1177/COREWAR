#include "../../includes/vm.h"

void	do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	char reg;
	unsigned int position;
	int value;

	if (!vm->mods->aff)
		return ;
	position = carriage->position;
	change_position(&position, 1);
	value = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	reg = (char)value;
	carriage->position = position;
	printf("aff\n");
}
