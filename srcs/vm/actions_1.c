/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:04:16 by clala             #+#    #+#             */
/*   Updated: 2020/07/03 15:05:14 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		set_live_vars(t_vm *vm, int num)
{
	t_player	*p;
	int			i;

	i = 0;
	p = vm->players->first_player;
	while (++i <= vm->players->qty && num > 0 && num <= vm->players->qty)
	{
		if (num == p->num)
		{
			p->last_live = vm->data->cycles;
			p->lives_in_period++;
			vm->players->last_alive_num = num;
			vs_players_refresh(vm);
			break ;
		}
		p = p->next;
	}
}

void			do_live(t_carriage *carriage, t_vm *vm)
{
	int			position;
	int			num;

	position = carriage->pos;
	carriage->last_cycle_alive = vm->data->cycles;
	change_position(&position, 1);
	num = -1 * get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	set_live_vars(vm, num);
	print_live(vm, carriage, num);
	carriage->pos = position;
	vm->data->lives_counter++;
	vs_state_refresh(vm);
}

void			do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int			values[2];
	int			position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena,
							carriage, &position, arguments[0]);
	values[1] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %d", values[0]);
		ft_printf(" r%d\n", values[1]);
	}
}

void			do_st(t_carriage *carriage,
			t_vm *vm, unsigned char *arguments)
{
	int			values[2];
	int			pos;
	int			reg;
	int			arg_2;

	pos = carriage->pos;
	change_position(&pos, 2);
	reg = vm->data->arena[pos];
	values[0] = get_arg_value(vm->data->arena, carriage, &pos, arguments[0]);
	if (arguments[1] == T_REG)
	{
		values[1] = get_reg_value(vm->data->arena, &pos);
		arg_2 = values[1];
		carriage->regs[values[1]] = values[0];
	}
	else
	{
		arg_2 = get_num_from_char(vm->data->arena, pos, 2);
		values[1] = arg_2 % IDX_MOD;
		change_position(&pos, 2);
		vs_push_cells(vm, norm_pos(carriage->pos + values[1]), carriage);
		write_reg(vm->data->arena, values[0], carriage->pos, values[1]);
	}
	vm->mods->verb_lvl & VERB_L3 ? print_st(carriage, reg, values, arg_2) : 0;
	carriage->pos = pos;
}
