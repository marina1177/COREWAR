#include "../../includes/vm.h"

void	do_sti(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;

	printf("sti\n");
	position = carriage->position;
	printf("position %d\noperation %d\n", position, vm->arena[position]);
	print_memory(&vm->arena[position], 1);
	change_position(&position, 2);
	printf("\nresize \n");
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->arena, carriage, &position, arguments[2]);
	write_reg(vm->arena, values[0], carriage->position, (values[1] + values[2]) % IDX_MOD);
	printf("position %d\n", position);
	carriage->position = position;
	print_memory(&vm->arena[position], 1);
	printf("final int %d %d %d\n", values[0], values[1], values[2]);
}

void	do_fork(t_carriage *carriage, t_vm *vm)
{
	int value;
	unsigned int position;
	t_carriage *new;
	int i;

	i = -1;
	position = carriage->position;
	change_position(&position, 1);
	value = get_arg_value(vm->arena, carriage, &position, T_DIR);
	carriage->position = position;
	new = make_new_carriage(value % IDX_MOD);
	while (++i <= REG_NUMBER)
		new->regs[i] = carriage->regs[i];
	new->carry = carriage->carry;
	new->last_cycle_alive = carriage->last_cycle_alive; //здесь копируется номер цикла, в котором в последний раз выполнялась операция live
	add_carriage(&vm->carriages, new); //какое имя у каретки? что еще скопировать?
	printf("fork\n");
}

void	do_lld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	unsigned int position;
	unsigned int temp;

	position = carriage->position;
	change_position(&position, 2);
	if (arguments[0] == T_DIR)
		values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	else
	{
		temp = carriage->position;
		change_position(&temp, get_num_from_char(vm->arena, position, 2));
		values[0] = get_num_from_char(vm->arena, temp, IND_SIZE);
		change_position(&position, IND_SIZE);
	}
	values[1] = get_reg_value(vm->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->position = position;
	printf("lld\n");
}

void	do_lldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	unsigned int position;
	unsigned int temp;

	position = carriage->position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->arena, &position);
	temp = values[0] + values[1];
	carriage->regs[values[2]] = get_arg_value(vm->arena, carriage, &temp, T_IND);
	carriage->position = position;
	printf("lldi\n");
}

void	do_lfork(t_carriage *carriage, t_vm *vm)
{
	int value;
	unsigned int position;
	t_carriage *new;
	int i;

	i = -1;
	position = carriage->position;
	change_position(&position, 1);
	value = get_arg_value(vm->arena, carriage, &position, T_DIR);
	carriage->position = position;
	new = make_new_carriage(value);
	while (++i <= REG_NUMBER)
		new->regs[i] = carriage->regs[i];
	new->carry = carriage->carry;
	new->last_cycle_alive = carriage->last_cycle_alive; //здесь копируется номер цикла, в котором в последний раз выполнялась операция live
	add_carriage(&vm->carriages, new); //какое имя у каретки? что еще скопировать?
	printf("lfork\n");
}
