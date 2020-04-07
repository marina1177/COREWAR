#include "../../includes/vm.h"

void	do_live(t_carriage *carriage, t_vm *vm)
{
	unsigned int position;
	int num;

	position = carriage->pos;
	carriage->last_cycle_alive = vm->data->cycles;
	change_position(&position, 2);
	num = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	//TO DO разобраться со структурой Димы
	printf("live\n");
}

void	do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	unsigned int position;

	printf("ld\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_reg_value(vm->data->arena, &position);
	print_memory(&vm->data->arena[position], 2);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	printf("values[0] = %d values[1] = %d\n", values[0], values[1]);
	printf("reg[%d] = %d\n",values[1], carriage->regs[values[1]]);
	print_memory(&vm->data->arena[carriage->pos], 2);
}

void	do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	unsigned int position;
	int temp;

	printf("sti\n");
	position = carriage->pos;
	printf("position %d\noperation %d\n", position, vm->data->arena[position]);
	print_memory(&vm->data->arena[position], 1);
	change_position(&position, 2);
	printf("\nresize \n");
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	if (arguments[1] == T_REG)
		carriage->regs[values[1]] = values[0];
	else
	{
		temp = get_num_from_char(vm->data->arena, position, 2) % IDX_MOD;
		write_reg(vm->data->arena, values[0], carriage->pos, temp);
		change_position(&position, IND_SIZE);
	}
	printf("position %d\n", position);
	carriage->pos = position;
	print_memory(&vm->data->arena[position], 1);
	printf("final int %d %d %d\n", values[0], values[1], values[2]);
	printf("st\n");
}

void	do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	printf("add\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] + values[1]; //зачем здесь уменьшать?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
}

void	do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] - values[1]; //зачем здесь уменьшать ?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	// printf("sub\n");
	// printf("values[0] = %d values[1] = %d\n", values[0], values[1]);
	// printf("reg = %d\n", carriage->regs[3]);
	// print_memory(&vm->data->arena[carriage->pos], 1);
}
