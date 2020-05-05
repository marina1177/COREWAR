#include "../../includes/vm.h"

void	do_live(t_carriage *carriage, t_vm *vm)
{
	int position;
	int num;
	int i;
	t_player *p;

	p = vm->players->first_player;
	i = 0;
	position = carriage->pos;
	carriage->last_cycle_alive = vm->data->cycles;
	change_position(&position, 1);
	num = -1 * get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	if (num > 0 && num <= vm->players->qty)
	{
		while (++i <= vm->players->qty)
		{
	 		if (num == p->num)
	 		{
	 			p->last_live = vm->data->cycles;
				vm->players->last_alive_num = num;			
	 			break ;
	 		}
	 		p = p->next;
	 	}		
	}
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %d\n", -num);
	}
	if (num > 0 && num <= vm->players->qty && vm->mods->verbosity_level & VERB_L1)
		print_is_alive(num, get_player_by_number(vm->players, num)->name);
	carriage->pos = position;
	vm->data->lives_counter++;	
}

void	do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	int position;

	//printf("ld\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %d", values[0]);
		ft_printf(" r%d\n", values[1]);		
	}	
}

/*
** 
*/
void	do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	int position;
	int	reg;
	int temp_val;
	
	//print_t_carriage(carriage);
	position = carriage->pos;
	change_position(&position, 2);
	reg = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	temp_val = 0;	
	if (arguments[1] == T_REG)
	{
		values[1] = get_reg_value(vm->data->arena, &position);
		carriage->regs[values[1]] = values[0];
		
	}
	else
	{
		temp_val = get_num_from_char(vm->data->arena, position, 2);
		values[1] = temp_val % IDX_MOD;
		change_position(&position, 2);
		write_reg(vm->data->arena, values[0], carriage->pos, values[1]); //нужно ли здесь дополнительно усекать?
	}
	if (vm->mods->verbosity_level & VERB_L3)
	{	
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg);
		ft_printf(" %hd\n", values[1] < temp_val ? temp_val : values[1]);
	}
	carriage->pos = position;
	//print_t_carriage(carriage);	
}

void	do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int reg1_num;
	int reg2_num;

	//printf("add\n");
	position = carriage->pos;
	change_position(&position, 2);
	reg1_num = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	reg2_num = vm->data->arena[position];
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] + values[1]; //зачем здесь уменьшать?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{	
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg1_num);
		ft_printf(" r%d", reg2_num);
		ft_printf(" r%d\n", values[2]);
	}
}

void	do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int reg1;
	int reg2;

	position = carriage->pos;
	change_position(&position, 2);
	reg1 = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	reg2 = vm->data->arena[position];
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] - values[1]; //зачем здесь уменьшать ?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verbosity_level & VERB_L3)
	{	
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg1);
		ft_printf(" r%d", reg2);
		ft_printf(" r%d\n", values[2]);
	}
}
