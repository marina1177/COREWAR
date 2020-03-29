#include "../../includes/com.h"

void		tokenize(char**line)
{
	printf("tokenize_|%s|\n", &((*line)[g_data->x]));
	check_label(*line);
	skip_space(*line);
	check_new_line(*line, 1);
	check_op(*line);
	skip_space(*line);
	printf("end_line[%d]=%s\n", g_data->x, &((*line)[g_data->x]));
	check_new_line(*line, 2);
}

void		parse_str(char **line)
{
	int		start;

	printf("parse_str__%s",(*line));
	start = g_data->x;
	if ((*line)[g_data->x] != '\0')
	{
		printf("line[%d] =|%c|\n",g_data->x, (*line)[g_data->x] );
		if ((*line)[g_data->x] == '.' && (g_data->name_f == 0 || g_data->comm_f == 0))
		{
			printf("header\n");
			if( g_data->x == start)
				add_header(line);
			else
				error_event(ERR_NAMECOM);
			printf("after_header_line[%d] =%c\n",g_data->x, (*line)[g_data->x] );
		}
		else if ((*line)[g_data->x] == '\n' && ++g_data->x)
			check_new_line(*line, 0);
		else
			tokenize(line);
		skip_space(*line);
		if((*line)[g_data->x] == '\n')
			g_data->x++;
	}
	else
		return ;
}

void	parse_file()
{
	//char	*buf;
	char	*line;
	int		size;

	g_snum = 0;

	while ((size = get_line(g_data->fd_s, &line))
							&& !(g_data->x = 0)
							&& ++g_data->y)
	{
		while (line[g_data->x])
		{
			skip_comment(line);
			skip_space(line);
			printf("get_|%s|\n", line);
			if (&(line[g_data->x]) && line[g_data->x] )
			{
				parse_str(&line);
				printf("line = %u\n", line[g_data->x]);
			}
		}
		ft_strdel(&line);
	}
	if (size == -1)
		error_event(ERR_READING);
	//token_add(END);
}
