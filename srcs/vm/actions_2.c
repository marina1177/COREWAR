#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	printf("and\n");
}

void	do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] | values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	printf("or\n");
}

void	do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] ^ values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	printf("xor\n");
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int value;
	unsigned int position;

	printf("zjmp\n");
	if (!carriage->carry) //нужно ли устанавливать тут значение того. что операция не выполнилась?
		return ;
	position = carriage->pos;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	change_position(&carriage->pos, value % IDX_MOD);
}

void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;
	unsigned int i;

	printf("ldi\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	i = carriage->pos;
	change_position(&i, (values[0] + values[1]) % IDX_MOD);
	carriage->regs[values[2]] = get_num_from_char(vm->data->arena, i, 4);
	carriage->pos = position;
	printf("ldi result reg[%d] = %d stay at %d\n",values[2], carriage->regs[values[2]], carriage->pos);
}
