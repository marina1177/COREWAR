#include "../../includes/vm.h"

void	make_operation(t_vm *vm, t_carriage *carriage, unsigned char *arguments)
{
	if (g_op_tab[(int)carriage->op_code].arg_type)
		vm->exec[(int)carriage->op_code](carriage, vm, arguments);
	else
		vm->exec[(int)carriage->op_code](carriage, vm);
	carriage->cycles_countdown--;
}

int		get_arg_size(int op, unsigned char arg)
{
	if (arg == T_REG)
		return (1);
	else if (arg == T_IND)
		return (2);
	else if (arg == T_DIR)
		return (g_op_tab[op].t_dir_size);
	return 0;
}

void	change_position(int *position, int change)
{
	*position += change;
	if (*position >= MEM_SIZE)
		*position %= MEM_SIZE;
	else if (*position < 0)  //?
		*position += MEM_SIZE;
}

static void	skip_args(t_carriage *carriage, unsigned char *arguments)
{
	int change; // а если третий бит 00?
	int i;

	i = 0;
	change = 2;
	if (g_op_tab[(int)carriage->op_code].arg_type)
	{
		while(i < g_op_tab[(int)carriage->op_code].args_num)
		{
			change += get_arg_size(carriage->op_code, arguments[i]);
			i++;
		}
	}
	else
		change += g_op_tab[(int)carriage->op_code].t_dir_size;
	change_position(&carriage->pos, change);
	//printf("ошибка в аргс\n");
}

static int	valid_register(t_carriage *carriage, unsigned char *arena, int position, unsigned char *arguments)
{
	int i;

	i = 0;
	while (i < g_op_tab[(int)carriage->op_code].args_num)
	{
		if (arguments[i] == T_REG)
		{
			//printf("REG\n");
			change_position(&position, 1);
			// printf("arena\n");
			// print_byte(arena[position]);
			if (arena[position] < 1 || arena[position] > 16)
			{
				skip_args(carriage, arguments);
				//printf("NOT VALID REG %d\n", carriage->op_code);
				return (0);
			}
		}
		else
		{
			//printf("not REG\n");
			change_position(&position, get_arg_size(carriage->op_code, arguments[i]));
		}
		i++;
	}
	return (1);
}
static int		valid_args_types(t_carriage *carriage, unsigned char *types, unsigned char *arguments)
{
	int i;
	t_arg_types code;

	i = 0;
	//print_byte(*types);
	code.types = *types;
	arguments[0] = code.bit.first;
	arguments[1] = code.bit.second;
	arguments[2] = code.bit.third;
	while (i < g_op_tab[(int)carriage->op_code].args_num)
	{
		if (arguments[i] == 0x3)
			arguments[i] = 0x4;
		i++;
	}
	//printf("%d %d %d\n", arguments[0], arguments[1], arguments[2]);
	return 1;
}
//сдвигаем каретку, только если код невалидный
static int	valid_operation_code(t_carriage *carriage)
{
	if (carriage->op_code < LIVE_CODE || carriage->op_code > AFF_CODE)
	{
		change_position(&carriage->pos, 1);
		return (0);
	}
	return (1);
}


int	check_operation(unsigned char *arena, t_carriage *carriage, unsigned char *arguments)
{
	int position;

	position = carriage->pos;
	ft_bzero(arguments, 4);
	carriage->op_code = arena[carriage->pos];
	if (!valid_operation_code(carriage))
		return 0;
	change_position(&position, 1);
	if (g_op_tab[(int)carriage->op_code].arg_type)
	{
		if (!valid_args_types(carriage, &arena[position], arguments) || \
			!valid_register(carriage, arena, position, arguments))
		{
			skip_args(carriage, arguments);
			return 0;
		}
	}
	return (1);
}