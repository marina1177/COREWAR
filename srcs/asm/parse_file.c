/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:09:55 by bcharity          #+#    #+#             */
/*   Updated: 2020/07/22 19:32:36 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

void	tokenize(char **line)
{
	check_label(*line);
	skip_space(*line);
	check_new_line(*line, 1);
	check_op(*line);
	skip_space(*line);
	check_new_line(*line, 2);
}

void	parse_str(char **line)
{
	int	start;

	start = g_mdata->x;
	if ((*line)[g_mdata->x] != '\0')
	{
		if ((*line)[g_mdata->x] == '.'
				&& (g_mdata->name_f == 0 || g_mdata->comm_f == 0)
				&& (g_tkn_first == NULL && g_label_first == NULL))
		{
			if (g_mdata->x == start)
				add_header(line);
			else
				error_event(ERR_NAMECOM);
		}
		else if ((*line)[g_mdata->x] == '\n' && ++g_mdata->x)
			check_new_line(*line, 0);
		else if (g_mdata->name_f == 1 && g_mdata->comm_f == 1)
			tokenize(line);
		else if ((g_mdata->name_f == 0 || g_mdata->comm_f == 0))
			put_error("Lexical error: invalid instruction", 1);
		if (!((*line)[g_mdata->x]) || (*line)[g_mdata->x] == '\0')
			return ;
	}
}

void	parse_file(void)
{
	int		size;

	while ((size = get_line(g_mdata->fd_s, &g_mdata->line))
							&& !(g_mdata->x = 0)
							&& ++g_mdata->y)
	{
		while (g_mdata->line[g_mdata->x])
		{
			//printf("line=|%s|\n", g_mdata->line);
			skip_comment(g_mdata->line);
			skip_space(g_mdata->line);
			if (&(g_mdata->line[g_mdata->x]) && g_mdata->line[g_mdata->x])
				parse_str(&g_mdata->line);
		}
		ft_strdel(&g_mdata->line);
	}
	if (size == -1)
		error_event(ERR_READING);
}
