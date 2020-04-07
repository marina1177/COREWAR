#include "../../includes/vm.h"

void	do_sti(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	printf("sti\n");
	position = carriage->pos;
	printf("position %d\noperation %d\n", position, vm->data->arena[position]);
	print_memory(&vm->data->arena[position], 1);
	change_position(&position, 2);
	printf("\nresize \n");
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->data->arena, carriage, &position, arguments[2]);
	write_reg(vm->data->arena, values[0], carriage->pos, (values[1] + values[2]) % IDX_MOD);
	printf("position %d\n", position);
	carriage->pos = position;
	print_memory(&vm->data->arena[position], 1);
	printf("final int %d %d %d\n", values[0], values[1], values[2]);
}

void	do_fork(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;

	position = carriage->pos;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	carriage->pos = position;
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	vm->carr->head->pos = value % IDX_MOD;
	printf("fork\n");
}

void	do_lld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	int position;
	int temp;

	position = carriage->pos;
	change_position(&position, 2);
	if (arguments[0] == T_DIR)
		values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	else
	{
		temp = carriage->pos;
		change_position(&temp, get_num_from_char(vm->data->arena, position, 2));
		values[0] = get_num_from_char(vm->data->arena, temp, DIR_SIZE);
		change_position(&position, IND_SIZE);
	}
	values[1] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	printf("lld result reg[%d] = %d stay at %d\n",values[1], carriage->regs[values[1]], carriage->pos);
}

void	do_lldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int temp;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	temp = carriage->pos;
	change_position(&temp, values[0] + values[1]);
	carriage->regs[values[2]] = get_num_from_char(vm->data->arena, temp, 4);
	carriage->pos = position;
	printf("lldi result reg[%d] = %d stay at %d\n",values[2], carriage->regs[values[2]], carriage->pos);
}

void	do_lfork(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;
	//t_carriage *new;
	//int pos;

	position = carriage->pos;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	carriage->pos = position;
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	vm->carr->head->pos = value; //здесь можем вылететь из арены предлагаю так
	//position = carriage->pos;
	//pos = carriage->pos;
	// change_position(&position, 1);
	// change_position(&pos, get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	// t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	// vm->carr->head->pos = pos;
	// carriage->pos = position;
	printf("lfork\n");
}
