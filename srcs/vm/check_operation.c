#include "../../includes/vm.h"

void	make_operation(t_vm *vm, t_carriage *carriage, unsigned char *arguments)
{
	if (g_op_tab[(int)carriage->op_code].arg_type)
		vm->exec[(int)carriage->op_code](carriage, vm, arguments);
	else
		vm->exec[(int)carriage->op_code](carriage, vm);	
}

int		get_arg_size(int op, unsigned char arg)
{
	if (arg == REG_CODE)
		return (1);
	else if (arg == IND_CODE)
		return (2);
	else if (arg == DIR_CODE)
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
			//ft_printf("skip %d\n", change);
			i++;
		}
	}
	else
		change += g_op_tab[(int)carriage->op_code].t_dir_size;
	change_position(&carriage->pos, change);
}

static int	valid_register(t_carriage *carriage, unsigned char *arena, int position, unsigned char *arguments)
{
	int i;

	i = 0;
	
	while (i < g_op_tab[(int)carriage->op_code].args_num)
	{
		if (arguments[i] == T_REG)
		{
			change_position(&position, 1);
			if (arena[position] < 1 || arena[position] > 16)
				return (0);
		}
		else
		{
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
	// print_byte(*types);
	// print_memory(types, 4);
	code.types = *types;
	arguments[0] = code.bit.first;
	arguments[1] = code.bit.second;
	arguments[2] = code.bit.third;
	while (i < g_op_tab[(int)carriage->op_code].args_num)
	{
		if (!(arguments[i] & g_op_tab[(int)carriage->op_code].arr[i]))
		{
			//printf("NOT VALID CODE\n");
			return 0;
		}
		i++;
	}
	//printf("%d %d %d\n", arguments[0], arguments[1], arguments[2]);
	return 1;
}
//сдвигаем каретку, только если код невалидный
int	valid_operation_code(t_carriage *carriage)
{	
	
	if (carriage->op_code < LIVE_CODE || carriage->op_code > AFF_CODE)
	{
		change_position(&carriage->pos, 1);
		return (0);
	}
	//write(1, "valid\n", 6);
	return (1);
}


int	check_operation(unsigned char *arena, t_carriage *carriage, unsigned char *arguments)
{
	int position;

	position = carriage->pos;
	ft_bzero(arguments, 4);
	//carriage->op_code = arena[carriage->pos];		
	if (!valid_operation_code(carriage))
		return 0;
	change_position(&position, 1);
	
	if (g_op_tab[(int)carriage->op_code].arg_type)
	{
		//ft_printf("check args\n");
		if (!valid_args_types(carriage, &arena[position], arguments) || \
			!valid_register(carriage, arena, position, arguments))
		{
			//ft_printf("args are not OK\n");
			skip_args(carriage, arguments);
			return 0;
		}
		//ft_printf("args are ok\n");
	}
	return (1);
}