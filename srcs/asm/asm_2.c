#include "../../includes/com.h"

t_token	*new_token()
{
	t_token		*new;

	new = NULL;
	if (!(new = (t_token*)malloc(sizeof(t_token))))
		error_event(ERR_ALLOC);
	new->status = -1;
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

	/*t_token		*tmp = g_tkn_first;
	while(tmp->next != NULL)
	{
		printf("--tmp_offset = %d****tmp_numbyte = %d--",
			 tmp->offset, tmp->num_byte_op);

		tmp = tmp->next;
	}
	printf("\n");
	*/

	return (new);
}


t_token		*join_token( int indx_op)
{
	t_token		*new;

	//printf("join_token\n");
	new = NULL;
	new = new_token();
	new->op = &(g_op_tab[indx_op]);
		return(new);
}

int		add_token(char *s, int size, t_2b token_type, int indx_op)
{
	printf("add_token\n");
	if (token_type & LABEL)
	{
		add_lbl(s, size);
	}
	if (token_type & INSTRUCTION)
	{
		join_token(indx_op);
		s += ft_strlen((g_op_tab[indx_op]).name);
		s = skip_space(s);
		parse_op(s);

	}
	return (0);
	//printf("-------------%s_\n",(g_op_tab[1]).name);
}

void	check_dup_label()
{
	t_lbl_lst *tmp;

	tmp = g_label_first;
	while(tmp != g_label_last)
	{
		if(!ft_strcmp(tmp->label, g_label_last->label))
			error_event(ERR_LABEL_DUB);
		tmp = tmp->next;
	}
}

void	add_lbl(char *s, const int size)
{
	t_lbl_lst	*new;

	printf("add_label_s[%d] = %s\n", size, s);

	if (!(new = (t_lbl_lst *)malloc(sizeof(t_lbl_lst))))
		error_event(ERR_ALLOC);
	new->next = NULL;
	if ((g_tkn_last == NULL && g_tkn_first == NULL))
	{
		g_label_first = new;
		g_label_last = g_label_first;
		new->offset = 0;
	}
	else
	{
		if (g_label_first == NULL && g_label_last == NULL)
		{
			g_label_first = new;
			g_label_last = g_label_first;
		}
		else
		{
			g_label_last->next = new;
		}
		new->offset = g_tkn_last->offset
			+ g_tkn_last->num_byte_op;
	}
	g_label_last = new;
	if (!(g_label_last->label = (char *)malloc(sizeof(char) * (size + 1))))
		error_event(ERR_ALLOC);
	ft_strncpy(g_label_last->label, s, size);
	check_dup_label();
	/*printf("label_last->label= %s\nlabel_last->offset = %ld\n",
	 g_label_last->label, g_label_last->offset);*/

}
