#include "../../includes/vm.h"

void		do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	char	reg;
	int		position;
	int		value;

	if (!vm->mods->aff)
	{
		change_position(&carriage->pos, 3);
		return ;
	}	
	position = carriage->pos;
	change_position(&position, 2);
	value = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	reg = (char)value;	
	carriage->pos = position;
	if (vm->mods->aff)
		ft_printf("Aff: %c\n", reg);	
}
