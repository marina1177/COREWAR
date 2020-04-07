/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_operations_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorent <jflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:23:35 by clianne           #+#    #+#             */
/*   Updated: 2020/02/13 16:27:45 by jflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		sub(t_carriage *curr, t_vm *vm)
{
	int		temp;
	int		num[2];

	temp = curr->pos;
	increase_position(&temp, 2);
	num[0] = vm->data->arena[temp];
	increase_position(&temp, 1);
	num[1] = vm->data->arena[temp];
	increase_position(&temp, 1);
	curr->regs[vm->data->arena[temp] - 1] = \
		curr->regs[num[0] - 1] - curr->regs[num[1] - 1];
	curr->carry = curr->regs[vm->data->arena[temp] - 1] == 0 ? 1 : 0;
}

void		and(t_carriage *curr, t_vm *vm)
{
	int		temp;
	unsigned char	args[4];
	int				num[2];

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	num[0] = get_one_arg(&temp, args[0], curr, vm);
	num[1] = get_one_arg(&temp, args[1], curr, vm);
	curr->regs[vm->data->arena[temp] - 1] = num[0] & num[1];
	curr->carry = curr->regs[vm->data->arena[temp] - 1] == 0 ? 1 : 0;
}

void		do_iarray_fill(int *arr, int size, int val)
{
	int		i;

	i = -1;
	while (++i < size)
		arr[i] = val;
}

void				or(t_carriage *curr, t_vm *vm)
{
	int				temp;
	unsigned char	args[4];
	int				num[2];

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	do_iarray_fill(num, 2, 0);
	num[0] = get_one_arg(&temp, args[0], curr, vm);
	num[1] = get_one_arg(&temp, args[1], curr, vm);
	curr->regs[vm->data->arena[temp] - 1] = num[0] | num[1];
	curr->carry = curr->regs[vm->data->arena[temp] - 1] == 0 ? 1 : 0;
}

void		xor(t_carriage *curr, t_vm *vm)
{
	int				temp;
	unsigned char	args[4];
	int				num[2];

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	do_iarray_fill(num, 2, 0);
	num[0] = get_one_arg(&temp, args[0], curr, vm);
	num[1] = get_one_arg(&temp, args[1], curr, vm);
	curr->regs[vm->data->arena[temp] - 1] = num[0] ^ num[1];
	curr->carry = curr->regs[vm->data->arena[temp] - 1] == 0 ? 1 : 0;
}
