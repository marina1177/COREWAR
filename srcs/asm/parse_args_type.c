/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:04:21 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 16:04:23 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_emptyline(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (IS_BLANK(line[i]))
			i++;
		else if (line[i] == '\n')
		{
			g_tkn_last->new_line += 1;
			i++;
		}
		else
			return (0);
	}
	line[0] = '\0';
	return (i);
}

static int		is_end_arg(char *line)
{
	int	i;

	i = 0;
	while (line[i] != SEPARATOR_CHAR)
	{
		if (!IS_BLANK(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void			parse_args_type(u_int16_t i, char *line)
{
	int	size;

	size = 0;
	while (line[g_mdata->x + size] != SEPARATOR_CHAR
			&& (line[g_mdata->x + size] != '\n'
				&& line[g_mdata->x + size] != '\0'))
	{
		if ((i == g_tkn_last->op->args_num - 1
			&& is_emptyline(&(line[g_mdata->x + size]))))
			break ;
		if (IS_BLANK(line[g_mdata->x + size])
				&& is_end_arg(&(line[g_mdata->x + size])))
			break ;
		size++;
	}
	if (check_reg(line, size, i) || check_dir(line, size, i)
			|| check_ind(line, size, i))
	{
		g_tkn_last->args[i]->arg = ft_strsub(line, g_mdata->x, size);
		return ;
	}
	else
		put_error(ERR_ARGTP, 1);
}
