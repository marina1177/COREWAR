#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	//int temp;

	position = carriage->pos;
	change_position(&position, 2);
	//temp = position;
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);		
		ft_printf(" %d", values[0]);
		ft_printf(" %d", values[1]);		
		ft_printf(" r%d", values[2]);
		ft_printf("\n");
	}
	/*
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		if (arguments[0] == REG_CODE)
			ft_printf(" %d", values[0]);
		else if (arguments[0] == IND_CODE)
			ft_printf(" %d", values[2]);
		else
			ft_printf(" %d", values[0]);
		if (arguments[1] == REG_CODE)
			ft_printf(" %d", values[1]);
		else if (arguments[1] == IND_CODE)
			ft_printf(" %d", values[2]);
		else
			ft_printf(" %d", values[1]);
		ft_printf(" r%d\n", values[2]);
	}
	*/
	//printf("and\n");
}

void	do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] | values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);		
		ft_printf(" %d", values[0]);
		ft_printf(" %d", values[1]);		
		ft_printf(" r%d", values[2]);
		ft_printf("\n");
	}
}

void	do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] ^ values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	//printf("xor\n");
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);		
		ft_printf(" %d", values[0]);
		ft_printf(" %d", values[1]);		
		ft_printf(" r%d", values[2]);
		ft_printf("\n");
	}
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;
	int temp_pos;

	//printf("zjmp\n");
	//printf("position = %d\n", carriage->pos);
	//ft_printf("zjmp: carry = %d\n", carriage->carry);
	position = carriage->pos;
	change_position(&position, 1);
	temp_pos = position;
	value = get_arg_value(vm->data->arena, carriage, &position,
		g_op_tab[(int)carriage->op_code].t_dir_size);
	if (!carriage->carry) //нужно ли устанавливать тут значение того. что операция не выполнилась?
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
		if (!carriage->carry)
			ft_printf(" FAILED");
		else
			ft_printf(" OK");
		ft_printf("\n");
	}
}

void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int i;
	int temp_pos;

	//printf("ldi\n");
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
	{		
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		(arguments[0] == DIR_CODE) ?
			ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
		(arguments[1] == DIR_CODE) ?	
			ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
		ft_printf(" r%d", values[2]);
		ft_printf("\n");
		if (arguments[0] == DIR_CODE && arguments[1] == DIR_CODE)
			ft_printf("       | -> load from %hd + %hd = %d (with pc and mod %d)",
			values[0], values[1], (short)values[0] + (short)values[1],
			temp_pos + ((short)values[0] + (short)values[1]) % IDX_MOD);
		else if (arguments[0] == DIR_CODE)
			ft_printf("       | -> load from %hd + %d = %d (with pc and mod %d)",
			values[0], values[1], (short)values[0] + values[1],
			temp_pos + ((short)values[0] + values[1]) % IDX_MOD);
		else if (arguments[1] == DIR_CODE)
			ft_printf("       | -> load from %d + %hd = %d (with pc and mod %d)",
			values[0], values[1], values[0] + (short)values[1],
			temp_pos + (values[0] + (short)values[1]) % IDX_MOD);
		else
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
			values[0], values[1], values[0] + values[1],
			temp_pos + (values[0] + values[1]) % IDX_MOD);
		ft_printf("\n");
	}
	//printf("ldi result reg[%d] = %d stay at %d\n",values[2], carriage->regs[values[2]], carriage->pos);
}
