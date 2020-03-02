#include "com.h"
/*void	int_to_hex(int32_t dec, int dir_size, u_int32_t *place)
{
	int			move;
	int			buf;

	buf = dir_size;
	move = 0;
	while (dir_size)
	{
		//g_buf[*place + dir_size - 1] = (u_int8_t)((dec >> move) & 0xFF);
		move += 8;
		dir_size--;
	}
	*place += buf;
}
*/
t_token	*new_token()
{
	t_token		*new;


	new = NULL;
	if (!(new = (t_token*)malloc(sizeof(t_token))))
		error();
	new->status = -1;
	new->next = NULL;
	new->prev = NULL;
	if (g_tkn_last == NULL && g_tkn_first == NULL)
	{
		g_tkn_first = new;
		new->offset = 0;
	}
	else
	{
		g_tkn_last->next = new;
		new->prev = g_tkn_last;
		new->offset = g_tkn_last->offset
				+ g_tkn_last->num_byte_op;
	}
	g_tkn_last = new;
	return (new);
}


t_token		*join_token( int indx_op)
{
	t_token		*new;

	printf("join_token\n");
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
		printf("g_tkn_last->op->name = %s\n", g_tkn_last->op->name);
		s += ft_strlen((g_op_tab[indx_op]).name);
		s = skip_space(s);
		parse_op(s);

	}
	return (0);
	printf("-------------%s_\n",(g_op_tab[1]).name);
}

void	add_lbl(char *s, const int size)
{
	t_lbl_lst	*new;

	printf("add_label_s[%d] = %s\n", size, s);

	if (!(new = (t_lbl_lst *)malloc(sizeof(t_lbl_lst))))
		error();
	new->next = NULL;
	if ((g_label_last == NULL && g_label_first == NULL))
	{
		g_label_first = new;
		new->offset = 0;
	}
	else
	{
		g_label_last->next = new;
		if (g_data->tkn_lst == NULL)
			new->offset = 0;
		else
			new->offset = g_tkn_last->offset
				+ g_tkn_last->num_byte_op;
	}
	g_label_last = new;
	if (!(g_label_last->label = (char *)malloc(sizeof(char) * (size + 1))))
		error();
	ft_strncpy(g_label_last->label, s, size);

	/*printf("label_last->label= %s\nlabel_last->offset = %ld\n",
	 g_label_last->label, g_label_last->offset);*/
}
