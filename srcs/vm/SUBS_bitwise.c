/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorent <jflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:43:14 by jflorent          #+#    #+#             */
/*   Updated: 2020/02/13 15:58:17 by jflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int			get_num_from_char(int *pos, t_vm *vm, int num_size)
{
	int		num;
	int		i;
	char	pos_value;

	num = 0;
	i = -1;
	pos_value = vm->data->arena[*pos];
	while (++i < num_size)
	{
		num |= (unsigned char)(pos_value) << (8 * (num_size - 1 - i));
		increase_position(pos, 1);
	}
	return (num);
}

static int			get_int_from_char(int *pos, t_vm *vm)
{
	return (get_num_from_char(pos, vm, sizeof(int)));
}

static int			get_short_from_char(int *pos, t_vm *vm)
{
	return (get_num_from_char(pos, vm, sizeof(short)));
}

int					get_int(int *pos, t_carriage *curr,
							t_vm *vm, int size)
{
	if (((vm->op_tab)[curr->opcode].dir_size == 0 && size != 2) ||
		size == 4)
		return (get_int_from_char(pos, vm));
	else if ((vm->op_tab)[curr->opcode].dir_size == 1 ||
		size == 2)
		return (get_short_from_char(pos, vm));
	return (0);
}

void				set_int(int *pos, int num, t_vm *vm)
{
	char			temp;

	temp = (num & 0xff000000) >> 24;
	vm->data->arena[*pos] = temp;
	increase_position(pos, 1);
	temp = (num & 0x00ff0000) >> 16;
	vm->data->arena[*pos] = temp;
	increase_position(pos, 1);
	temp = (num & 0x0000ff00) >> 8;
	vm->data->arena[*pos] = temp;
	increase_position(pos, 1);
	temp = (num & 0x000000ff);
	vm->data->arena[*pos] = temp;
}