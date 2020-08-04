/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_code_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 14:26:50 by root              #+#    #+#             */
/*   Updated: 2020/08/03 22:37:03 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

char	*write_code(t_dasm *ds, char *str)
{
	char	*for_free;

	if (ds->champ_code)
	{
		for_free = ds->champ_code;
		ds->champ_code = ft_strjoin(ds->champ_code, str);
		free(for_free);
		return (ds->champ_code);
	}
	else
	{
		ds->champ_code = ft_strdup(str);
		return (ds->champ_code);
	}
}

int		neg_numb_conversion(unsigned int value, int byte)
{
	int					ret;
	unsigned short int	value3;

	if (value > CHAMP_MAX_SIZE)
	{
		if (byte == 2)
		{
			value3 = value - 1;
			value3 = value3 ^ MASK2;
			ret = value3;
		}
		else if (byte == 4)
		{
			value = value - 1;
			value = value ^ MASK4;
			ret = value;
		}
		return (ret * (-1));
	}
	ret = value;
	return (ret);
}
