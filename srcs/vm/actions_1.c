#include "../../includes/vm.h"

void	do_live(t_carriage *carriage, t_vm *vm)
{
	unsigned int position;
	int num;

	position = carriage->position;
	carriage->last_cycle_alive = vm->data->cycles;
	change_position(&position, 2);
	num = get_arg_value(vm->arena, carriage, &position, T_DIR);
	//TO DO разобраться со структурой Димы
	printf("live\n");
}

void	do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	unsigned int position;

	printf("ld\n");
	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_reg_value(vm->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->position = position;
	printf("result reg[%d] = %d stay at %d\n",values[1], carriage->regs[values[1]], carriage->position);
	//print_memory(&vm->arena[carriage->position], 2);
}

void	do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	unsigned int position;

	position = carriage->position;
	change_position(&position, 2);
	carriage->regs[3] = 23;
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	if (arguments[1] == T_REG)
		carriage->regs[get_reg_value(vm->arena, &position)] = values[0];
	else
	{
		values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
		write_reg(vm->arena, values[0], carriage->position, values[1]); //нужно ли здесь дополнительно усекать?
	}
	carriage->position = position;
	print_memory(vm->arena, 16);
	printf("expect arena[%d] changed stay at %d\n", values[1], position);
}

void	do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	printf("add\n");
	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	carriage->regs[values[2]] = values[0] + values[1]; //зачем здесь уменьшать?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
}

void	do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	carriage->regs[values[2]] = values[0] - values[1]; //зачем здесь уменьшать ?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->position = position;
	// printf("sub\n");
	// printf("values[0] = %d values[1] = %d\n", values[0], values[1]);
	// printf("reg = %d\n", carriage->regs[3]);
	// print_memory(&vm->arena[carriage->position], 1);
}
