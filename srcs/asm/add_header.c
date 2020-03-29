#include "../../includes/com.h"

void	valid_headlen(t_2b type_h, int len)
{
	if ((type_h == NAME && len > 128))
		error_event(ERR_CHNAME_LEN);
	else if (type_h == COMMENT && len > 2048)
		error_event(ERR_CHCOMM_LEN);
}

void	put_header(char *str, int len, t_2b type_h)
{
	if (type_h == NAME)
	{
		ft_strncpy(g_data->head->prog_name, &(str[g_data->x]), len - 1);
		g_data->name_f += 1;
	}
	else if (type_h == COMMENT)
	{
		ft_strncpy(g_data->head->comment,&(str[g_data->x]), len - 1);
		g_data->comm_f += 1;
	}
	else
		error_event(ERR_NAMECOM);
}

void	process_header(char **line, t_2b type_h)
{
	int		len;
	char	*str;
	char	*temp;

	temp = 0;
	str = *line;
	while (!(len = ft_findchar(str + g_data->x, '\"'))
			&& get_line(g_data->fd_s, &temp) && ++g_data->y)
		ft_strmerge(&str, &temp);
	if (!len)
		error_line(ERR_STR_STOP, str, 0);
	valid_headlen(type_h, len);
	put_header(str, len, type_h);
	*line = str;
	g_data->x += len;
	skip_space(str);
	if(str[g_data->x] == '\n')
		g_data->x++;
	else
		error_event(ERR_NAMECOM);
}

t_2b	exist_header(char **line)
{
	char	*p;
	t_2b	type;

	type = 0;
	if ((p = ft_strstr(&((*line)[g_data->x]), NAME_CMD_STRING)) != NULL
			&& p == &((*line)[g_data->x]) && g_data->name_f == 0)
	{
		type = NAME;
		g_data->x += ft_strlen(NAME_CMD_STRING);
	}
	else if((p = ft_strstr(&((*line)[g_data->x]), COMMENT_CMD_STRING))!= NULL
				 && p == &((*line)[g_data->x]) && g_data->comm_f == 0)
	{
		type = COMMENT;
		g_data->x += ft_strlen(COMMENT_CMD_STRING);
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
	if ((*line)[g_data->x] == '\"' && ++g_data->x)
		process_header(line, type);
	else
		error_event(ERR_NAMECOM);
	while((*line)[g_data->x] != '\n' && (*line)[g_data->x] != '\0')
	{
		if (IS_BLANK((*line)[g_data->x]))
			g_data->x++;
		else
			error_event(ERR_NAMECOM);
	}
	//printf("prog_name =%s\ncomment=%s\n", g_data->head->prog_name, g_data->head->comment);
	//printf("line = %s\nline[%d] = %s\n",line, g_data->x, &(line[g_data->x]));
}
