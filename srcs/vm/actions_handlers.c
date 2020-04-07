#include "../../includes/vm.h"

int			get_num_from_char(unsigned char *arena, unsigned int position, int size)
{
	int		*num;
	int		i;
	char	arguments[5];

	i = size;
	ft_bzero(arguments, 5);
	while (--i >= 0)
	{
		arguments[i] = arena[position];
		change_position(&position, 1);
	}
	print_memory(arguments, size);
	num = (int *)arguments;
	return (*num);
}

int		get_reg_value(unsigned char *arena, unsigned int *pos)
{
	int result;

	result = arena[*pos];
	printf("REG = %d\n", result);
	change_position(pos, 1);
	return (result);
}

int		get_arg_value(unsigned char *arena, t_carriage *car,  unsigned int *pos, char arg_type)
{
	 unsigned int temp;
	int result;

	if (arg_type == T_REG)
	{
		result = car->regs[arena[*pos]];
		print_memory(&arena[*pos], 1);
		printf("%d", result);
		change_position(pos, 1);
	}
	else if (arg_type == T_DIR)
	{
		result = get_num_from_char(arena, *pos, g_op_tab[(int)car->op_code].t_dir_size);
		change_position(pos, g_op_tab[(int)car->op_code].t_dir_size);
	}
	else if (arg_type == T_IND)
	{
		temp = car->pos;
		change_position(&temp, get_num_from_char(arena, *pos, 2) % IDX_MOD);
		result = get_num_from_char(arena, temp, IND_SIZE);
		change_position(pos, IND_SIZE);
	}
	return (result);
}

void	write_reg(unsigned char *arena, int reg,  unsigned int position, int change)
{
	char			temp;

	change_position(&position, change);
	temp = (reg & 0xff000000) >> 24;
	arena[position] = temp;
	change_position(&position, 1);
	temp = (reg & 0x00ff0000) >> 16;
	arena[position] = temp;
	change_position(&position, 1);
	temp = (reg & 0x0000ff00) >> 8;
	arena[position] = temp;
	change_position(&position, 1);
	temp = (reg & 0x000000ff);
	arena[position] = temp;
	printf("here");
	print_memory(&arena[position - 4], 4);
	//print_memory(arena, MEM_SIZE);
}
