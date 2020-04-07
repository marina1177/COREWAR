/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_operations_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorent <jflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:11:36 by jflorent          #+#    #+#             */
/*   Updated: 2020/02/13 16:28:47 by jflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		zjmp(t_carriage *curr, t_vm *vm)
{
	int		temp;
	int				num;

	if (curr->carry == 0)
		return ;
	temp = curr->pos;
	increase_position(&temp, 1);
	num = get_int(&temp, curr, vm, 2);
	curr->pos += (num % IDX_MOD);
}

void		ldi(t_carriage *curr, t_vm *vm)
{
	int		temp;
	unsigned char	args[4];
	int				num[2];
	char			reg;
	int				res;

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	num[0] = get_one_arg(&temp, args[0], curr, vm);
	num[1] = get_one_arg(&temp, args[1], curr, vm);
	reg = temp;
	temp = curr->pos;
	increase_position(&temp, ((num[0] + num[1]) % IDX_MOD));
	res = get_int(&temp, curr, vm, 4);
	curr->regs[reg - 1] = res;
}

void		sti(t_carriage *curr, t_vm *vm)
{
	int		temp;
	unsigned char	args[4];
	int				num[2];
	int				res;

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	res = curr->regs[vm->data->arena[temp] - 1];
	increase_position(&temp, 1);
	num[0] = get_one_arg(&temp, args[1], curr, vm);
	num[1] = get_one_arg(&temp, args[2], curr, vm);
	temp = curr->pos;
	increase_position(&temp, ((num[0] + num[1]) % IDX_MOD));
	set_int(&temp, res, vm);
}

void		cwfork(t_carriage *curr, t_vm *vm)
{
	int		num;
	int		temp;

	temp = curr->pos;
	increase_position(&temp, 1);
	num = get_int(&temp, curr, vm, 2);
	temp = curr->pos;
	increase_position(&temp, (num % IDX_MOD));
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, curr));
}
