/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:46:53 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 13:46:53 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

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
			g_tkn_last->new_line +=1;
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
	while (line[g_data->x + size] != SEPARATOR_CHAR
			&& (line[g_data->x + size] != '\n'
				&& line[g_data->x + size] != '\0'))
	{
		if ((i == g_tkn_last->op->args_num - 1
			&& is_emptyline(&(line[g_data->x + size]))))
			break ;
		if (IS_BLANK(line[g_data->x + size]) && is_end_arg(&(line[g_data->x + size])))
			break ;
		size++;
	}
	if (check_reg(line, size, i) || check_dir(line, size, i)
			|| check_ind(line, size, i))
	{
		g_tkn_last->args[i]->arg = ft_strsub(line, g_data->x, size);
		return ;
	}
	else
		put_error(ERR_ARGTP, 1);
}
