/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:16:40 by clala             #+#    #+#             */
/*   Updated: 2020/07/03 15:09:18 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	do_sti(t_carriage *carr, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;
	int	temp;
	int	reg;

	position = carr->pos;
	temp = carr->pos;
	change_position(&position, 2);
	reg = vm->data->arena[position];
	values[0] = get_arg_value(vm->data->arena,
				carr, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena,
				carr, &position, arguments[1]);
	values[2] = get_arg_value(vm->data->arena,
				carr, &position, arguments[2]);
	vs_push_cells(vm, norm_pos(carr->pos + (values[1] + values[2]) % IDX_MOD),
				carr);
	write_reg(vm->data->arena, values[0], carr->pos,
				(values[1] + values[2]) % IDX_MOD);
	carr->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | %s", carr->num, g_op_tab[carr->op_code].name);
		print_sti(arguments, temp, values, reg);
	}
}

void	do_fork(t_carriage *carriage, t_vm *vm)
{
	int	value;
	int	position;
	int	temp;

	position = carriage->pos;
	temp = position;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	change_position(&vm->carr->head->pos, value % IDX_MOD);
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %hd (%hd)", value, temp + (value % IDX_MOD));
		ft_printf("\n");
	}
	vs_state_refresh(vm);
}

void	do_lld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[2];
	int	position;
	int	temp;

	position = carriage->pos;
	change_position(&position, 2);
	if (arguments[0] == T_DIR)
		values[0] = get_arg_value(vm->data->arena,
					carriage, &position, arguments[0]);
	else
	{
		temp = carriage->pos;
		change_position(&temp, get_num_from_char(vm->data->arena, position, 2));
		values[0] = get_num_from_char(vm->data->arena, temp, DIR_SIZE);
		change_position(&position, IND_SIZE);
	}
	values[1] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
		print_lld(carriage, arguments, values);
}

void	do_lldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int	values[3];
	int	position;
	int	temp;
	int	temp_pos;

	position = carriage->pos;
	temp_pos = position;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena,
				carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	temp = carriage->pos;
	change_position(&temp, values[0] + values[1]);
	carriage->regs[values[2]] = get_num_from_char(vm->data->arena, temp, 4);
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
		print_lldi(carriage, arguments, values, temp_pos);
}

void	do_lfork(t_carriage *carriage, t_vm *vm)
{
	int	value;
	int	position;
	int	temp;

	temp = carriage->pos;
	position = carriage->pos;
	change_position(&position, 1);
	value = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	t_carriages_push(vm->carr, t_carriage_copy(vm->carr, carriage));
	change_position(&vm->carr->head->pos, value);
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %hd (%hd)", value,
			temp + value);
		ft_printf("\n");
	}
}
