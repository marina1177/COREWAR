/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_code_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 14:24:09 by root              #+#    #+#             */
/*   Updated: 2020/08/03 22:37:03 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

int		write_tdir2(t_dasm *ds, int value)
{
	if (!(write_code(ds, _SPACE_)))
		return (0);
	if (!(write_code(ds, "%")))
		return (0);
	if (!(write_code(ds, ft_itoa(value))))
		return (0);
	return (1);
}

int		write_tdir(t_dasm *ds, int opr)
{
	unsigned short int	byte2;
	unsigned int		byte4;
	char				*bt;
	int					k;

	k = 0;
	if (g_op_tab[opr].t_dir_size == 2)
	{
		bt = (char*)&byte2;
		ds->ccs += 2;
		if (read_byte(bt, 2, ds->fd))
			k = neg_numb_conversion(byte2, 2);
		else
			return (0);
	}
	else if (g_op_tab[opr].t_dir_size == 4)
	{
		bt = (char*)&byte4;
		ds->ccs += 4;
		if (read_byte(bt, 4, ds->fd))
			k = neg_numb_conversion(byte4, 4);
		else
			return (0);
	}
	return (write_tdir2(ds, k));
}

int		write_treg(t_dasm *ds)
{
	unsigned char	reg;
	int				k;

	k = read(ds->fd, &reg, 1);
	if (k == 1)
	{
		ds->ccs += k;
		k = reg;
		write_code(ds, _SPACE_);
		write_code(ds, "r");
		write_code(ds, ft_itoa(k));
		return (1);
	}
	return (0);
}

int		write_tind(t_dasm *ds)
{
	unsigned short int	h;
	int					k;
	char				*bt;

	bt = (char*)&h;
	if (read_byte(bt, 2, ds->fd))
	{
		ds->ccs += 2;
		k = neg_numb_conversion(h, 2);
		write_code(ds, _SPACE_);
		write_code(ds, ft_itoa(k));
		return (1);
	}
	return (0);
}

void	write_arg(t_dasm *ds, int opr, char type)
{
	if (type == 1)
	{
		write_treg(ds);
	}
	else if (type == 2)
	{
		write_tdir(ds, opr);
	}
	else if (type == 3)
		write_tind(ds);
}
