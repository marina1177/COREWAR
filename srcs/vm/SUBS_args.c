/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorent <jflorent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:20:01 by jflorent          #+#    #+#             */
/*   Updated: 2020/02/07 11:31:29 by jflorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			get_one_arg(int *temp, unsigned char code,
									t_carriage *curr, t_vm *vm)
{
	int		num;
	int		mod_temp;

	num = 0;
	if (code == 1)
	{
		num = curr->regs[vm->data->arena[*temp] - 1];
		increase_position(temp, 1);
	}
	else if (code == 2)
		num = get_int(temp, curr, vm, 0);
	else if (code == 3)
	{
		mod_temp = curr->pos +
					get_int(temp, curr, vm, 2) % IDX_MOD;
		num = get_int(&mod_temp, curr, vm, 4);
	}
	return (num);
}

int			get_one_arg_no_md(int *temp, unsigned char code,
						t_carriage *curr, t_vm *vm)
{
	int		num;
	int		mod_temp;

	num = 0;
	if (code == 1)
	{
		num = curr->regs[vm->data->arena[*temp] - 1];
		increase_position(temp, 1);
	}
	else if (code == 2)
		num = get_int(temp, curr, vm, 0);
	else if (code == 3)
	{
		mod_temp = curr->pos +
					get_int(temp, curr, vm, 2);
		if (curr->opcode == 0x0d)
			num = get_int(&mod_temp, curr, vm, 2);
		else
			num = get_int(&mod_temp, curr, vm, 4);
	}
	return (num);
}