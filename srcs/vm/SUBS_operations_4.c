/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_operations_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorent <jflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:17:15 by jflorent          #+#    #+#             */
/*   Updated: 2020/02/15 09:11:41 by jflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		lld(t_carriage *curr, t_vm *vm)
{
	int				temp;
	unsigned char	args[4];
	int				num;
	char			reg;

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);
	num = get_one_arg_no_md(&temp, args[0], curr, vm);
	temp = curr->pos;
	args[0] == 2 ? increase_position(&temp, 6) : increase_position(&temp, 4);
	reg = vm->data->arena[temp];
	curr->regs[reg - 1] = num;
	curr->carry = num == 0 ? 1 : 0;
}

void		lldi(t_carriage *curr, t_vm *vm)
{
	int				temp;
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
	reg = vm->data->arena[temp];
	temp = curr->pos;
	increase_position(&temp, (num[0] + num[1]));
	res = get_int(&temp, curr, vm, 4);
	curr->regs[reg - 1] = res;
	curr->carry = res == 0 ? 1 : 0;
}

void		lfork(t_carriage *curr, t_vm *vm)
{
	int		num;
	int		temp;

	temp = curr->pos;
	increase_position(&temp, 1);
	num = get_int(&temp, curr, vm, 2);
	increase_position(&temp, num);
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, curr));
	vm->carr->head->pos = temp;
}

void		aff(t_carriage *curr, t_vm *vm)
{
	int		temp;

	if (!vm->mods->aff)
		return ;
	temp = curr->pos;
	increase_position(&temp, 2);
	ft_printf("Aff: %c\n", (char)curr->regs[vm->data->arena[temp] - 1]);
}
