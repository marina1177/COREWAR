#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	print_bitwise_op(vm, carriage, values);
}

void	do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] | values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	print_bitwise_op(vm, carriage, values);
}

void	do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] ^ values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	print_bitwise_op(vm, carriage, values);	
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int	value;
	int	position;
	int	temp_pos;

	position = carriage->pos;
	change_position(&position, 1);
	temp_pos = position;
	value = get_arg_value(vm->data->arena, carriage, &position,
		g_op_tab[(int)carriage->op_code].t_dir_size);
	if (!carriage->carry)
	{
		change_position(&temp_pos, g_op_tab[(int)carriage->op_code].t_dir_size);
		carriage->pos = temp_pos;
	}
	else
		change_position(&carriage->pos, value % IDX_MOD);
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %hd", value);
		!carriage->carry ? ft_printf(" FAILED\n") :	ft_printf(" OK\n");
	}
}

void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;
	int	i;
	int	temp_pos;

	position = carriage->pos;
	temp_pos = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	i = carriage->pos;
	change_position(&i, (values[0] + values[1]) % IDX_MOD);
	carriage->regs[values[2]] = get_num_from_char(vm->data->arena, i, 4);
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
		print_ldi(carriage, arguments, values, temp_pos);
}
