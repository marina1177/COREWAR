/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 15:40:13 by bcharity          #+#    #+#             */
/*   Updated: 2020/07/22 22:05:33 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	valid_headlen(t_2b type_h, int len)
{
	if ((type_h == NAME && len >= PROG_NAME_LENGTH))
		error_event(ERR_CHNAME_LEN);
	else if (type_h == COMMENT && len >= COMMENT_LENGTH)
		error_event(ERR_CHCOMM_LEN);
}

void	put_header(char *str, int len, t_2b type_h)
{
	if (type_h == NAME)
	{
		ft_strncpy(g_mdata->head->prog_name, &(str[g_mdata->x]), len - 1);
		g_mdata->name_f += 1;
	}
	else if (type_h == COMMENT)
	{
		ft_strncpy(g_mdata->head->comment, &(str[g_mdata->x]), len - 1);
		g_mdata->comm_f += 1;
	}
	else
		error_event(ERR_NAMECOM);
}

void	process_header(char **line, t_2b type_h)
{
	int		len;
	char	*str;
	char	*temp;
	int		start_line;

	temp = 0;
	str = *line;
	start_line = g_mdata->y;
	while (!(len = ft_findchar(str + g_mdata->x, '\"'))
			&& get_line(g_mdata->fd_s, &temp) && ++g_mdata->y)
		ft_strmerge(&str, &temp);
	*line = str;
	if (!len)
		error_line(ERR_STR_STOP, start_line);
	valid_headlen(type_h, len);
	put_header(str, len, type_h);
	*line = str;
	g_mdata->x += len;
	skip_space(str);
	if (str[g_mdata->x] == '\n')
		g_mdata->x++;
	else
		error_event(ERR_NAMECOM);
}

t_2b	exist_header(char **line)
{
	char	*p;
	t_2b	type;

	type = 0;
	if ((p = ft_strstr(&((*line)[g_mdata->x]), NAME_CMD_STRING)) != NULL
			&& p == &((*line)[g_mdata->x]) && g_mdata->name_f == 0)
	{
		type = NAME;
		g_mdata->x += ft_strlen(NAME_CMD_STRING);
	}
	else if ((p = ft_strstr(&((*line)[g_mdata->x]), COMMENT_CMD_STRING)) != NULL
			&& p == &((*line)[g_mdata->x]) && g_mdata->comm_f == 0)
	{
		type = COMMENT;
		g_mdata->x += ft_strlen(COMMENT_CMD_STRING);
	}
	else
		error_event(ERR_NAMECOM);
	return (type);
}

void	add_header(char **line)
{
	t_2b	type;

	type = exist_header(line);
	skip_space(*line);
	if ((*line)[g_mdata->x] == '\"' && ++g_mdata->x)
		process_header(line, type);
	else
		error_event(ERR_NAMECOM);
	while ((*line)[g_mdata->x] != '\n' && (*line)[g_mdata->x] != '\0')
	{
		if (IS_BLANK((*line)[g_mdata->x]))
			g_mdata->x++;
		else
			error_event(ERR_NAMECOM);
	}
}
