#include "../../includes/com.h"

int		search_op(char *line)
{
	static const char	*types[17] = {NULL, "live", "ld", "st", "add", "sub",
									"and", "or", "xor", "zjmp", "ldi", "sti",
									"fork", "lld", "lldi", "lfork", "aff"};
	size_t				size;
	int					i;

//	printf("search_op_%s_line[%d]=%s", line, g_data->x, &(line[g_data->x]));
	i = 17;
	while (--i)
	{
		size = ft_strlen(types[i]);
		//printf("strnequ_line[%d]=%s\n", g_data->x, &(line[g_data->x]));
		if (ft_strnequ(&(line[g_data->x]), types[i], size))
			break ;
	}
	printf("opcode = %d\n", i);
//	printf("line[%d]=%s\n", g_data->x, &(line[g_data->x]));
	if (i == 0)
		put_error("Lexical error: invalid instruction", 1);
	g_data->x += size;
	//printf("line[%d]=%s\n", g_data->x, &(line[g_data->x]));
	return (i - 1);

	//	solve_res(skip_space(s), op, a);
}

t_token	*new_token()
{
	t_token		*new;

	new = NULL;
	if (!(new = (t_token*)malloc(sizeof(t_token))))
		error_event(ERR_ALLOC);
	//new->status = -1;
	new->next = NULL;
	new->prev = NULL;
	if (g_tkn_last == NULL && g_tkn_first == NULL)
	{
		g_tkn_first = new;
		g_tkn_last = g_tkn_first;
		new->offset = 0;
		new->num_byte_op = 0;
	}
	else
	{
		g_tkn_last->next = new;
		new->prev = g_tkn_last;
		new->num_byte_op = 0;
		new->offset = g_tkn_last->offset
			+ g_tkn_last->num_byte_op;
	}
	//printf("BEFORE_EXEC_BYTES = %llu\n", g_data->exec_bytes);
	g_data->exec_bytes += g_tkn_last->num_byte_op;
	printf("EXEC_BYTES = %lu\n", g_data->exec_bytes);
	g_tkn_last = new;

	t_token		*tmp = g_tkn_first;
	while(tmp != NULL)
	{
		printf("--tmp_offset = %d****tmp_numbyte = %d--",
			 tmp->offset, tmp->num_byte_op);

		tmp = tmp->next;
	}
	printf("\n");

	return (new);
}

void	add_token(char *line, int indx_op)
{
	t_token		*new;

	printf("add_token__indx = %d\n", indx_op);

	new = NULL;
	new = new_token();
	new->op = &(g_op_tab[indx_op]);
	new->new_line = 0;

	printf("line[%d]=%s\n", g_data->x, &(line[g_data->x]));
}

void					check_op(char *line)
{
	//int	i;
	//int	opcode;

	printf("check_op_%s_line[%d]=%s", line, g_data->x, &(line[g_data->x]));
	if (!line[g_data->x])
		return ;
	add_token(line, search_op(line));

	g_tkn_last->num_byte_op = 1;
	if (g_tkn_last->op->args_types_code)
		g_tkn_last->num_byte_op += 1;

	skip_space(line);
	get_args(line);
	/*if (!validate_parameters(opcode->type, opcode->param_code))
		put_error("Syntax error: wrong parameters types", 1);*/
}

