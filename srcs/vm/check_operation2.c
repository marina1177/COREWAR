#include "../../includes/vm.h"

void	make_operation(t_vm *vm, t_carriage *carriage, unsigned char *arguments)
{
	if (g_op_tab[(int)carriage->op_code].arg_type)
		vm->exec[(int)carriage->op_code](carriage, vm, arguments);
	else
		vm->exec[(int)carriage->op_code](carriage, vm);	
}

int		get_arg_size(int op, unsigned char arg)
{
	if (arg == T_REG)
		return (1);
	else if (arg == T_IND)
		return (2);
	else if (arg == T_DIR)
		return (g_op_tab[op].t_dir_size);
	return 0;
}

void	change_position(int *position, int change)
{
	*position += change;
	if (*position >= MEM_SIZE)
		*position %= MEM_SIZE;
	else if (*position < 0)
	{
		*position %= MEM_SIZE;
		*position += MEM_SIZE;
	}	
}
