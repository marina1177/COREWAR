/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/08/03 22:37:03 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

int 	read_argument_without_types(t_dasm *ds, int opr)
{
	int 	i;

	i = 0;
	while (g_op_tab[opr].args_types[i] && i < 3)
	{
		if (g_op_tab[opr].args_types[i] == T_DIR)
			write_tdir(ds, opr);
		else if (g_op_tab[opr].args_types[i] == T_IND)
			write_tind(ds);
		else if (g_op_tab[opr].args_types[i] == T_REG)
			write_treg(ds);
		i++;
	}
	return (1);
}

int 	read_operation_argument(int opr, t_dasm *ds)
{
	unsigned char	type_arg;
	unsigned char	type;
	int 	i;

	i = 0;
	type = 0;
	if ((read(ds->fd, &type_arg, 1)) == 1)
	{
		ds->ccs++;
		while (g_op_tab[opr].args_types[i] && i < 3)
		{
			if (i == 0)
				type = type_arg;
			else if (i == 1)
				type = type_arg << 2;
			else if (i == 2)
				type = type_arg << 4;
			type = type >> 6;
			write_arg(ds, opr, type);
			if (i <= 1 && g_op_tab[opr].args_types[i + 1])
				write_code(ds, ",");
			i++;
		}
		return (1);
	}
	return (0);
}

int		read_champ_code(t_dasm *ds)
{
	char 	operation;
	int 	opr;
	int 	error;

	error = 1;
	while ((read(ds->fd, &operation, 1)) == 1 && operation >= 1 && operation <= 16)
	{
		ds->ccs++;
		opr = operation - 1;
		if (!(write_code(ds, g_op_tab[opr].name)))
			return (0);
		if (g_op_tab[opr].args_types_code)
			error = read_operation_argument(opr, ds);
		else
			error = read_argument_without_types(ds, opr);
		if (!error)
			return (0);
		if (!(write_code(ds, "\n")))
			return (0);
	}
	return (1);
}
