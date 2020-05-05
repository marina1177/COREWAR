/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_sti(unsigned char *arguments, int temp,
				int *values, t_carriage *carriage, int reg)
{
	ft_printf("P %4d | ", carriage->num);
	ft_printf("%s", g_op_tab[carriage->op_code].name);
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