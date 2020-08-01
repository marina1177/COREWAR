/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:16:59 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 11:18:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		skip_args(t_carriage *carriage, unsigned char *arguments)
{
	int			change;
	int			i;

	i = 0;
	change = 2;
	if (g_op_tab[(int)carriage->op_code].arg_type)
	{
		while (i < g_op_tab[(int)carriage->op_code].args_num)
		{
			change += get_arg_size(carriage->op_code, arguments[i]);
			i++;
		}
	}
	else
		change += g_op_tab[(int)carriage->op_code].t_dir_size;
	change_position(&carriage->pos, change);
}

static int		valid_register(t_carriage *carriage,
			unsigned char *arena, int position, unsigned char *arguments)
{
	int			i;

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
			change_position(&position,
				get_arg_size(carriage->op_code, arguments[i]));
		}
		i++;
	}
	return (1);
}

static int		valid_args_types(t_carriage *carriage, unsigned char *types,
				unsigned char *arguments)
{
	int			i;
	t_arg_types	code;

	i = 0;
	code.types = *types;
	arguments[0] = code.bit.first == IND_CODE ? T_IND : code.bit.first;
	arguments[1] = code.bit.second == IND_CODE ? T_IND : code.bit.second;
	arguments[2] = code.bit.third == IND_CODE ? T_IND : code.bit.third;
	while (i < g_op_tab[(int)carriage->op_code].args_num)
	{
		if (!(arguments[i] & g_op_tab[(int)carriage->op_code].arr[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int				valid_operation_code(t_carriage *carriage)
{
	if (carriage->op_code < LIVE_CODE || carriage->op_code > AFF_CODE)
	{
		change_position(&carriage->pos, 1);
		return (0);
	}
	return (1);
}

int				check_operation(unsigned char *arena, t_carriage *carriage,
						unsigned char *arguments)
{
	int			position;

	position = carriage->pos;
	ft_bzero(arguments, 4);
	if (!valid_operation_code(carriage))
		return (0);
	change_position(&position, 1);
	if (g_op_tab[(int)carriage->op_code].arg_type)
	{
		if (!valid_args_types(carriage, &arena[position], arguments) || \
			!valid_register(carriage, arena, position, arguments))
		{
			skip_args(carriage, arguments);
			return (0);
		}
	}
	return (1);
}
