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

void	print_lldi(t_carriage *carriage, unsigned char *arguments,
			int *values, int temp_pos)
{
	ft_printf("P %4d | ", carriage->num);
	ft_printf("%s", g_op_tab[carriage->op_code].name);
	(arguments[0] == T_DIR) ?
	ft_printf(" %hd", values[0]) : ft_printf(" %d", values[0]);
	(values[1] == T_DIR) ?
	ft_printf(" %hd", values[1]) : ft_printf(" %d", values[1]);
	ft_printf(" r%d", values[2]);
	ft_printf("\n");
	if (arguments[0] == T_DIR && values[1] == T_DIR)
		ft_printf("       | -> load from %hd + %hd = %d (with pc %d)",
		values[0], values[1], (short)values[0] + (short)values[1],
		(temp_pos + ((short)values[0] + (short)values[1])));
	else if (arguments[0] == DIR_CODE)
		ft_printf("       | -> load from %hd + %d = %d (with pc %d)",
		values[0], values[1], (short)values[0] + values[1],
		(temp_pos + ((short)values[0] + values[1])));
	else if (values[1] == DIR_CODE)
		ft_printf("       | -> load from %d + %hd = %d (with pc %d)",
		values[0], values[1], values[0] + (short)values[1],
		(temp_pos + (values[0] + (short)values[1])));
	else
		ft_printf("       | -> load from %d + %d = %d (with pc %d)",
		values[0], values[1], values[0] + values[1],
		(temp_pos + (values[0] + values[1])));
	ft_printf("\n");
}