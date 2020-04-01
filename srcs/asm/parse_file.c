/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:09:55 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 15:04:51 by bcharity         ###   ########.fr       */
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

	start = g_data->x;
	if ((*line)[g_data->x] != '\0')
	{
		if ((*line)[g_data->x] == '.' && (g_data->name_f == 0 || g_data->comm_f == 0)
				&& (g_tkn_first == NULL && g_label_first == NULL))
		{
			if ( g_data->x == start)
				add_header(line);
			else
				error_event(ERR_NAMECOM);
		}
		else if ((*line)[g_data->x] == '\n' && ++g_data->x)
			check_new_line(*line, 0);
		else if (g_data->name_f == 1 && g_data->comm_f == 1)
			tokenize(line);
		else if ((g_data->name_f == 0 || g_data->comm_f == 0))
			put_error("Lexical error: invalid instruction", 1);
//		skip_space(*line);
		if (!((*line)[g_data->x]) || (*line)[g_data->x] == '\0')
			return ;
/*		if ((*line)[g_data->x] == '\n')
			g_data->x++;*/
	}
}

void	parse_file()
{
	char	*line;
	int		size;

	while ((size = get_line(g_data->fd_s, &line))
							&& !(g_data->x = 0)
							&& ++g_data->y)
	{
		while (line[g_data->x])
		{
			skip_comment(line);
			skip_space(line);
			if (&(line[g_data->x]) && line[g_data->x] )
				parse_str(&line);
		}
		ft_strdel(&line);
	}
	if (size == -1)
		error_event(ERR_READING);
}

