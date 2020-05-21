/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:16:47 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:16:48 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	char	reg;
	int		position;
	int		value;

	if (!vm->mods->aff)
	{
		change_position(&carriage->pos, 3);
		return ;
	}
	position = carriage->pos;
	change_position(&position, 2);
	value = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	reg = (char)value;
	carriage->pos = position;
	if (vm->mods->aff)
		ft_printf("Aff: %c\n", reg);
}

void			do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int			values[3];
	int			position;
	int			reg1_num;
	int			reg2_num;

	position = carriage->pos;
	change_position(&position, 2);
	reg1_num = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[0]);
	reg2_num = vm->data->arena[position];
	values[1] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] + values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg1_num);
		ft_printf(" r%d", reg2_num);
		ft_printf(" r%d\n", values[2]);
	}
}

void			do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int			values[3];
	int			position;
	int			reg1;
	int			reg2;

	position = carriage->pos;
	change_position(&position, 2);
	reg1 = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[0]);
	reg2 = vm->data->arena[position];
	values[1] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] - values[1];
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" r%d", reg1);
		ft_printf(" r%d", reg2);
		ft_printf(" r%d\n", values[2]);
	}
}
