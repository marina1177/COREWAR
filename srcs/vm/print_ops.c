/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/05/11 21:56:46 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_sti(unsigned char *arguments, int temp,
				int *values, int reg)
{
	ft_printf(" r%d", reg);
	(arguments[1] == T_DIR) ?
	ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
	(arguments[2] == T_DIR) ?
	ft_printf(" %hd\n", values[2]) : ft_printf(" %d\n", values[2]);
	if (arguments[1] == T_DIR && arguments[2] == T_DIR)
		ft_printf("       | -> store to %hd + %hd = %d (with pc and mod %d)",
		values[1], values[2], (short)values[1] + (short)values[2],
		temp + ((short)values[1] + (short)values[2]) % IDX_MOD);
	else if (values[1] == T_DIR)
		ft_printf("       | -> store to %hd + %d = %d (with pc and mod %d)",
		values[1], values[2], (short)values[1] + values[2],
		temp + ((short)values[1] + values[2]) % IDX_MOD);
	else if (arguments[2] == T_DIR)
		ft_printf("       | -> store to %d + %hd = %d (with pc and mod %d)",
		values[1], values[2], values[1] + (short)values[2],
		temp + (values[1] + (short)values[2]) % IDX_MOD);
	else
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		values[1], values[2], values[1] + values[2],
		temp + (values[1] + values[2]) % IDX_MOD);
	ft_printf("\n");
}

int		print_st(t_carriage *carriage, int reg, int *values, int temp_val)
{
	ft_printf("P %4d | ", carriage->num);
	ft_printf("%s", g_op_tab[carriage->op_code].name);
	ft_printf(" r%d", reg);
	ft_printf(" %hd\n", values[1] < temp_val ? temp_val : values[1]);
	return (1);
}

void	print_live(t_vm *vm, t_carriage *carriage, int num)
{
	if (vm->mods->verb_lvl & VERB_L3)
	{
		ft_printf("P %4d | ", carriage->num);
		ft_printf("%s", g_op_tab[carriage->op_code].name);
		ft_printf(" %d\n", -num);
	}
	if (num > 0 && num <= vm->players->qty &&
		vm->mods->verb_lvl & VERB_L1)
		print_is_alive(num, get_player_by_number(vm->players, num)->name);
}

void	print_ldi(t_carriage *carriage, unsigned char *arguments,
				int *values, int temp_pos)
{
	ft_printf("P %4d | ", carriage->num);
	ft_printf("%s", g_op_tab[carriage->op_code].name);
	(arguments[0] == T_DIR) ?
		ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
	(arguments[1] == T_DIR) ?
		ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
	ft_printf(" r%d", values[2]);
	ft_printf("\n");
	if (arguments[0] == T_DIR && arguments[1] == T_DIR)
		ft_printf("       | -> load from %hd + %hd = %d (with pc and mod %d)",
		values[0], values[1], (short)values[0] + (short)values[1],
		temp_pos + ((short)values[0] + (short)values[1]) % IDX_MOD);
	else if (arguments[0] == DIR_CODE)
		ft_printf("       | -> load from %hd + %d = %d (with pc and mod %d)",
		values[0], values[1], (short)values[0] + values[1],
		temp_pos + ((short)values[0] + values[1]) % IDX_MOD);
	else if (arguments[1] == DIR_CODE)
		ft_printf("       | -> load from %d + %hd = %d (with pc and mod %d)",
		values[0], values[1], values[0] + (short)values[1],
		temp_pos + (values[0] + (short)values[1]) % IDX_MOD);
	else
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
		values[0], values[1], values[0] + values[1],
		temp_pos + (values[0] + values[1]) % IDX_MOD);
	ft_printf("\n");
}

void	print_lld(t_carriage *carriage, unsigned char *arguments, int *values)
{
	ft_printf("P %4d | ", carriage->num);
	ft_printf("%s", g_op_tab[carriage->op_code].name);
	(arguments[0] == T_IND) ?
	ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
	ft_printf(" r%d\n", values[1]);
}
