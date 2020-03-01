#include "../includes/com.h"

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

void	need_address_label(t_token *new)
{
	t_token		*p;

	p = g_label_first;
	while (p != new)
	{
		//if((*p).status == 0)
			//конвертировать адрес и добавитьв строку
	}
}

/*void	join_label()
{
	t_token		*new;

	new = new_token();
	new->label = g_label_last->label;
	new->status = -2;
	//++ пройти по всем листам и узнать, не требуется ли адрес нового лайбла
	//для аргумента инструкции
	need_address_label(new);
}*/

parse_op(char *op)
{
	char	**lex;

	lex = ft_strsplit(op,  SEPARATOR_CHAR);
	int i = 0;
	while (lex && *lex)
	{
		printf("lex[%d] = %s\n", i, *lex);
		i++;
	}

}

t_token		*join_token(t_2b token_type, int indx_op)
{
	t_token		*new;

	if (token_type && INSTRUCTION)
	{
		/*if (g_tkn_last->status == -2)
			new = g_tkn_last;*/
		new = new_token();
		new->op = &(g_op_tab[indx_op]);
		return(new);
	}
}

int		add_token(char *s, int size, t_2b token_type, int indx_op)
{
	t_lbl_lst	lst_lbl;
	t_token		*new;

	if (token_type && LABEL)
	{
		lst_lbl = *add_lbl(s, size);
	}
	if (token_type && INSTRUCTION)
	{
		new = join_token(token_type, indx_op);
		s += ft_strlen((g_op_tab[indx_op]).name);
		s = skip_space(s);
		parse_str(s);

	}

	return (0);
}
