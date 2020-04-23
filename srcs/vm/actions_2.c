#include "../../includes/vm.h"

void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] & values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
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
	//printf("or\n");
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
}

void	do_zjmp(t_carriage *carriage, t_vm *vm)
{
	int value;
	int position;

	//printf("zjmp\n");
	//printf("position = %d\n", carriage->pos);
	ft_printf("zjmp: carry = %d\n", carriage->carry);
	position = carriage->pos;
	change_position(&position, 1);	
	if (!carriage->carry) //нужно ли устанавливать тут значение того. что операция не выполнилась?
	{
		change_position(&position, g_op_tab[(int)carriage->op_code].t_dir_size);
		carriage->pos = position;
		return ;
	}	
	value = get_arg_value(vm->data->arena, carriage, &position, g_op_tab[(int)carriage->op_code].t_dir_size);
	ft_printf("value = %d, carry = %d\n", value, carriage->carry);
	change_position(&carriage->pos, value % IDX_MOD);
	//printf("position = %d\n", carriage->pos);
}

void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;
	int i;

	//printf("ldi\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	i = carriage->pos;
	change_position(&i, (values[0] + values[1]) % IDX_MOD);
	carriage->regs[values[2]] = get_num_from_char(vm->data->arena, i, 4);
	carriage->pos = position;
	//printf("ldi result reg[%d] = %d stay at %d\n",values[2], carriage->regs[values[2]], carriage->pos);
}
