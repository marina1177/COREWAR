#include "../../includes/vm.h"

int	get_negative_number(void *argument, int size)
{
	char num[5];
	int i;

	i = 0;
	ft_bzero(num, 5);
	while (i < size)
	{
		num[i] = ((char*)argument)[i];
		if (i == 0)
			num[i] -= 1;
		num[i] ^= 0xFF;
		i++;
	}
	return (*(int *)num * (-1));
}

int			get_num_from_char(unsigned char *arena, int position, int size)
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
	//print_memory(arguments, size);
	if (arguments[size - 1] & 0b10000000)
		return (get_negative_number((unsigned int *)arguments, size));
	num = (int *)arguments;
	return (*num);
}

int		get_reg_value(unsigned char *arena, int *pos)
{
	int result;

	result = arena[*pos];
	//printf("REG = %d\n", result);
	change_position(pos, 1);
	return (result);
}

int		get_arg_value(unsigned char *arena, t_carriage *car,  int *pos, char arg_type)
{
	int temp;
	int result;	
	
	result = 0;
	if (arg_type == REG_CODE)
	{
		result = car->regs[arena[*pos]];
		change_position(pos, 1);
	}
	else if (arg_type == DIR_CODE)
	{
		result = get_num_from_char(arena, *pos, g_op_tab[(int)car->op_code].t_dir_size);
		change_position(pos, g_op_tab[(int)car->op_code].t_dir_size);
	}
	else if (arg_type == IND_CODE)
	{
		
		temp = car->pos;
		change_position(&temp, get_num_from_char(arena, *pos, 2) % IDX_MOD);
		//printf("IND смещаемся на = %d\n", get_num_from_char(arena, *pos, 2) % IDX_MOD);
		result = get_num_from_char(arena, temp, DIR_SIZE);
		//printf("IND скопировали %d\n", result);
		change_position(pos, IND_SIZE);
	}
	return (result);
}

void	write_reg(unsigned char *arena, int reg,  int position, int change)
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
	//printf("here");
	//print_memory(&arena[position - 4], 4);
	//print_memory(arena, MEM_SIZE);
}
