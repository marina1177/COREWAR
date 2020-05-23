/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:16:53 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:16:54 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			get_num_from_char(unsigned char *arena, int position, int size)
{
	int		*num;
	int		i;
	char	arguments[5];
	short int *q;
	q = NULL;
	i = size;
	ft_bzero(arguments, 5);
	while (--i >= 0)
	{
		arguments[i] = arena[position];
		change_position(&position, 1);
	}
	if (size == 2)
	{
		q = (short int *)arguments;
		return(*q);
	}
	num = (int *)arguments;
	return (*num);
}


int			get_reg_value(unsigned char *arena, int *pos)
{
	int		result;

	result = arena[*pos];
	change_position(pos, 1);
	return (result);
}

int			get_arg_value(unsigned char *arena, t_carriage *car,
			int *pos, char arg_type)
{
	int temp;
	int result;

	result = 0;
	if (arg_type == T_REG)
	{
		result = car->regs[arena[*pos]];
		change_position(pos, 1);
	}
	else if (arg_type == T_DIR)
	{
		result = get_num_from_char(arena, *pos,
				g_op_tab[(int)car->op_code].t_dir_size);
		change_position(pos, g_op_tab[(int)car->op_code].t_dir_size);
	}
	else if (arg_type == T_IND)
	{
		temp = car->pos;
		change_position(&temp, get_num_from_char(arena, *pos, 2) % IDX_MOD);
		result = get_num_from_char(arena, temp, DIR_SIZE);
		change_position(pos, IND_SIZE);
	}
	return (result);
}

void		write_reg(unsigned char *arena, int reg,
			int position, int change)
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
}
