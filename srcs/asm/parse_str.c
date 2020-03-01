#include "../includes/com.h"

t_lbl_lst	*add_lbl(char *s, const int size)
{
	t_lbl_lst	*new;

	printf("add_label_s[%d] = %s\n", size, s);

	if (!(new = (t_lbl_lst *)malloc(sizeof(t_lbl_lst))));
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

	printf("add_label_g= %s\n", g_label_last->label);

}

char *skip_space(char *s)
{
	while(*s == ' ' || *s == '	')
		s++;
	return(s);
}

char *skip_comment(char *s)
{
	char	*pnt;

	pnt = ft_strstr(s, "#");
	if (pnt != NULL)
		*pnt = '\0';
	pnt = ft_strstr(s, ";");
	if (pnt != NULL)
		*pnt = '\0';
	return(s);
}

void	solve_res(char *s, char *op, int a)
{
	int		lbllen;
	char	*pnt;

	if (*s != '\0' && (op == NULL || op != &(s[0])))
	{
		lbllen = 0;
		while (s[lbllen] == LABEL_CHARS)
			lbllen++;
		if (s[lbllen] == ':')
		{
			add_token(&(s[0]), lbllen, LABEL, -1);
			printf("after add_token(LABEL) = %s\n",s);
		}
		else
		{
			printf("where label_:_???\n");
			error();
		}
		pnt = skip_space(&(s[lbllen]));
		if (pnt == op)
		{
			add_token(op, 0, INSTRUCTION, a);
			printf("after add_token(INSTR) = %s\n",s);
		}
		else
		{
			printf("wtf after label:???\n");
			error();
		}
	}
	else if (op == &(s[0]) && a > 0)
	{
		add_token(op, 0, INSTRUCTION, a);
		printf("after add_token(INSTR) = %s\n",s);
	}
}

int search_op(char *s)
{
	int		a;
	char	*op;

	a = -1;
	(op = ft_strstr(s, "live")) != NULL ? a = 0 : -1;
	(op = ft_strstr(s, "ld")) != NULL ? a = 1 : -1;
	(op = ft_strstr(s, "st")) != NULL ? a = 2 : -1;
	(op = ft_strstr(s, "add")) != NULL ? a = 3 : -1;
	(op = ft_strstr(s, "sub")) != NULL ? a = 4 : -1;
	(op = ft_strstr(s, "and")) != NULL ? a = 5 : -1;
	(op = ft_strstr(s, "or")) != NULL ? a = 6 : -1;
	(op = ft_strstr(s, "xor")) != NULL ? a = 7 : -1;
	(op = ft_strstr(s, "zjmp")) != NULL ? a = 8 : -1;
	(op = ft_strstr(s, "ldi")) != NULL ? a = 9 : -1;
	(op = ft_strstr(s, "sti")) != NULL ? a = 10 : -1;
	(op = ft_strstr(s, "fork")) != NULL ? a = 11 : -1;
	(op = ft_strstr(s, "lld")) != NULL ? a = 12 : -1;
	(op = ft_strstr(s, "lldi")) != NULL ? a = 13 : -1;
	(op = ft_strstr(s, "lfork")) != NULL ? a = 14 : -1;
	(op = ft_strstr(s, "aff")) != NULL ? a = 15 : -1;
	solve_res(s, op, a);
}

void	tokenize(char *s)
{
	char	*pnt;
	int		i;

	printf("tokenize = %s\n",s);

	if (*s == '.')
	{
		add_header(s, i, STRING);
	}

	search_op(s); //indx структуры g_op_tab[16]

	return ;

}

int		parse_str(char **buf)
{
	char	*pnt;
	int		i;

	i = 0;
	pnt = skip_comment(buf);
	pnt = skip_space(buf);

	if (*pnt != '\0')
		tokenize(pnt);
	else
		return (0);



	printf("pnt = %s\n", pnt);
}
