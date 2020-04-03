#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("and\n");
}

void	do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	carriage->regs[values[2]] = values[0] | values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("or\n");
}

void	do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	carriage->regs[values[2]] = values[0] ^ values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	printf("xor\n");
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int value;
	unsigned int position;

	printf("zjmp\n");
	if (!carriage->carry) //нужно ли устанавливать тут значение того. что операция не выполнилась?
		return ;
	position = carriage->position;
	change_position(&position, 1);
	value = get_arg_value(vm->arena, carriage, &position, T_DIR);
	carriage->position += value % IDX_MOD;
}

void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;
	unsigned int i;

	printf("ldi\n");
	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	i = (values[0] + values[1]) % IDX_MOD;
	carriage->regs[values[2]] = get_arg_value(vm->arena, carriage, &i, T_IND);
	carriage->position = position;
	printf("values[0] = %d values[1] = %d values[2] = %d\n", values[0], values[1]);
	printf("reg[%d] = %d\n",values[1], carriage->regs[values[1]]);
	print_memory(&vm->arena[carriage->position], 2);
}
