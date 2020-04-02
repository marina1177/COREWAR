#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, char *arguments)
{
	int values[3];
	int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->arena, carriage, &position, arguments[2]);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("and\n");
}

void	do_or(t_carriage *carriage, t_vm *vm, char *arguments)
{
	int values[3];
	int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->arena, carriage, &position, arguments[2]);
	carriage->regs[values[2]] = values[0] | values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("or\n");
}

void	do_xor(t_carriage *carriage, t_vm *vm, char *arguments)
{
	int values[3];
	int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->arena, carriage, &position, arguments[2]);
	carriage->regs[values[2]] = values[0] ^ values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("xor\n");
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;

	printf("zjmp\n");
	if (!carriage->carry) //нужно ли устанавливать тут значение того. что операция не выполнилась?
		return ;
	position = carriage->position;
	change_position(&position, 1);
	value = get_arg_value(vm->arena, carriage, &position, T_DIR);
	carriage->position += value % IDX_MOD;
}

void	do_ldi(t_carriage *carriage, t_vm *vm, char *arguments)
{
	int values[3];
	int position;
	int res;
	int i;

	i = -1;
	printf("ldi\n");
	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	while (++i < 3)
	{
		values[i] = get_arg_value(vm->arena, carriage, &position, arguments[i]);
		if (i < 2 && arguments[i] == T_REG)
			values[i] = carriage->regs[values[i]];
	}
	i = (values[0] + values[1]) % IDX_MOD;
	carriage->regs[values[2]] = get_arg_value(vm->arena, carriage, &i, T_IND);
	carriage->position = position;
	
}
