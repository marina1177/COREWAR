/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:11:07 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 16:04:58 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

int		check_reg(char *line, int size, u_int16_t i)
{
	if (is_reg(&(line[g_mdata->x]), size)
			&& g_tkn_last->op->args_types[i] & T_REG)
	{
		g_tkn_last->args[i]->argtype = REGISTER;
		g_tkn_last->args[i]->argsize = 1;
		g_tkn_last->num_byte_op += 1;
		return (TRUE);
	}
	return (FALSE);
}

int		check_dir(char *line, int size, u_int16_t i)
{
	if (is_direct(&(line[g_mdata->x]), size)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args[i]->argtype = DIRECT;
		g_tkn_last->args[i]->argsize = g_tkn_last->op->t_dir_size;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;
		return (TRUE);
	}
	else if (is_dir_label(&(line[g_mdata->x]), size)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args[i]->argtype = DIRECT_LABEL;
		g_tkn_last->args[i]->argsize = g_tkn_last->op->t_dir_size;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;
		return (TRUE);
	}
	return (FALSE);
}

int		check_ind(char *line, int size, u_int16_t i)
{
	if (is_indirect(&(line[g_mdata->x]), size)
			&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args[i]->argtype = INDIRECT;
		g_tkn_last->args[i]->argsize = 2;
		g_tkn_last->num_byte_op += 2;
		return (TRUE);
	}
	else if (is_ind_label(&(line[g_mdata->x]), size)
		&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args[i]->argtype = INDIRECT_LABEL;
		g_tkn_last->args[i]->argsize = 2;
		g_tkn_last->num_byte_op += 2;
		return (TRUE);
	}
	return (FALSE);
}
