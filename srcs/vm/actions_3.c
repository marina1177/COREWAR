#include "../../includes/vm.h"

void	do_sti(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int temp;
	int	reg;

	position = carriage->pos;
	temp = carriage->pos;
	change_position(&position, 2);
	reg = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_arg_value(vm->data->arena, carriage, &position, arguments[2]);
	write_reg(vm->data->arena, values[0], carriage->pos, (values[1] + values[2]) % IDX_MOD);
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg);
		(arguments[1] == T_DIR) ?
		ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
		(arguments[2] == T_DIR) ?
		ft_printf(" %hd\n", values[2]) : ft_printf(" %d\n", values[2]);
		if (arguments[1] == T_DIR && arguments[2] == T_DIR)
			ft_printf("       | -> store to %hd + %hd = %d (with pc and mod %d)",
			values[1], values[2], (short)values[1] + (short)values[2],
			temp + ((short)values[1] + (short)values[2]) % IDX_MOD);
		else if (values[1] == T_DIR)
			ft_printf("       | -> store to %hd + %d = %d (with pc and mod %d)",
			values[1], values[2], (short)values[1] + values[2],
			temp + ((short)values[1] + values[2]) % IDX_MOD);
		else if (arguments[2] == T_DIR)
			ft_printf("       | -> store to %d + %hd = %d (with pc and mod %d)",
			values[1], values[2], values[1] + (short)values[2],
			temp + (values[1] + (short)values[2]) % IDX_MOD);
		else
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
			values[1], values[2], values[1] + values[2],
			temp + (values[1] + values[2]) % IDX_MOD);
		ft_printf("\n");
	}
}

void	do_fork(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;

	position = carriage->pos;
	//write(1, "fork\n", 5);
	//print_memory(&vm->data->arena[position], 6);
	//printf("fork position=%d\n", position);
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	//printf("value=%d position=%d\n", value, position);
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	change_position(&vm->carr->head->pos, value % IDX_MOD);
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);		
		ft_printf(" %hd (%hd)", carriage->pos,
			vm->carr->head->pos);
		ft_printf("\n");
	}
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
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		(arguments[0] == T_IND) ?
		ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
		ft_printf(" r%d", values[1]);
		ft_printf("\n");
	}
	//printf("lld result reg[%d] = %d stay at %d\n",values[1], carriage->regs[values[1]], carriage->pos);
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
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)	
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		(arguments[0] == T_DIR) ?
		ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
		(values[1] == T_DIR) ?
		ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
		ft_printf(" r%d", values[2]);
		ft_printf("\n");
		if (arguments[0] == T_DIR && values[1] == T_DIR)
			ft_printf("       | -> load from %hd + %hd = %d (with pc %d)",
			values[0], values[1], (short)values[0] + (short)values[1],
			(carriage->pos + ((short)values[0] + (short)values[1])));
		else if (arguments[0] == T_DIR)
			ft_printf("       | -> load from %hd + %d = %d (with pc %d)",
			values[0], values[1], (short)values[0] + values[1],
			(carriage->pos + ((short)values[0] + values[1])));
		else if (values[1] == T_DIR)
			ft_printf("       | -> load from %d + %hd = %d (with pc %d)",
			values[0], values[1], values[0] + (short)values[1],
			(carriage->pos + (values[0] + (short)values[1])));
		else
			ft_printf("       | -> load from %d + %d = %d (with pc %d)",
			values[0], values[1], values[0] + values[1],
			(carriage->pos + (values[0] + values[1])));
		ft_printf("\n");
	}
	//printf("lldi result reg[%d] = %d stay at %d\n",values[2], carriage->regs[values[2]], carriage->pos);
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
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	change_position(&vm->carr->head->pos, value);
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)	
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);		
		ft_printf(" %hd (%hd)", carriage->pos,
			vm->carr->head->pos);
		ft_printf("\n");
	}
	//printf("lfork\n");
}
