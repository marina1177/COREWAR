#include "../../includes/vm.h"

void	do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	char reg;
	int position;
	int value;

	if (!vm->mods->aff)
		return ;
	position = carriage->pos;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	reg = (char)value;
	ft_printf("%c", reg);
	carriage->pos = position;
	printf("aff\n");	
}
