/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:09:55 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/03 20:54:39 by bcharity         ###   ########.fr       */
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
/*		if ((*line)[g_mdata->x] == '\n')
			g_mdata->x++;*/
	}
}

void	parse_file(void)
{
	char	*line;
	int		size;

	while ((size = get_line(g_mdata->fd_s, &line))
							&& !(g_mdata->x = 0)
							&& ++g_mdata->y)
	{
		while (line[g_mdata->x])
		{
			skip_comment(line);
			skip_space(line);
			if (&(line[g_mdata->x]) && line[g_mdata->x])
				parse_str(&line);
		}
		ft_strdel(&line);
	}
	if (size == -1)
		error_event(ERR_READING);
}
