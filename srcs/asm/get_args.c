#include "../../includes/com.h"

static void				skip_to_separator(char *line)
{
	while (line[g_data->x] && !IS_BLANK(line[g_data->x])
		&& line[g_data->x] != SEPARATOR_CHAR)
	{
		++g_data->x;
	}
}

static size_t		count_word(char const *s, char c)
{
	char	*p;
	size_t	lns;

	if (!s)
		return (0);
	lns = 0;
	p = (char*)s;
	while (*p != '\0')
	{
		if (*p != c && (*(p + 1) == c || *(p + 1) == '\0'))
			lns++;
		p++;
	}
	return (lns);
}

t_opargs	*parse_parameter(char *line)
{
	t_opargs	*param;
	int			i;

	i = 0;
	param = NULL;
	if (line[g_data->x])
	{
		if (!(param = (t_opargs*)malloc(sizeof(t_opargs))))
			error_event(ERR_ALLOC);
		param->x = g_data->x;
		param->y = g_data->y;
		//param->value = 0;
		param->arg = NULL;
		//parse_args_type(&param, line);
	}
	return (param);
}

void			get_args(char *line)
{
	size_t		i;
	size_t		cw;

	i = 0;
	printf("get_args_line[%d]=%s\n", g_data->x, &(line[g_data->x]));
	cw = count_word(&(line[g_data->x]), SEPARATOR_CHAR);
	printf("count_word = %zu..vs..argsnum[%d]= %u\n", cw, g_tkn_last->op->code, g_tkn_last->op->args_num);
	if (cw != g_tkn_last->op->args_num)
		error_event(ERR_OP);

	while (i < cw)
	{
		skip_space(line);
		if ((g_tkn_last->args[i] = parse_parameter(line)))
		{
			parse_args_type(i, line);
			printf("tkn_offset = %d\ntkn_numbyte = %d\n", g_tkn_last->offset,
			g_tkn_last->num_byte_op);
			skip_to_separator(line);
			//printf("skip_to_separator_line[%d]=%s\n", g_data->x, &(line[g_data->x]));
			skip_space(line);
			if (line[g_data->x]
				&& (line[g_data->x++] != SEPARATOR_CHAR || i == cw - 1))
				put_error("Syntax error: wrong parameters", 1);
		}
		++i;
	}
}
