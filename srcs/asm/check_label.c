#include "../../includes/com.h"

void	check_new_line(char *line, int f)
{
	if (!(&(line[g_data->x])) || line[g_data->x] == '\0')
	{
		//printf("return\n");
		return ;
	}
	//printf("check_new_line_|%s|\n", &(line[g_data->x]));
	if (line[g_data->x] == '\n')
	{
		if(f == 2)
		{
			if(g_tkn_last)
				g_tkn_last->new_line += 1;
		}
		if(f == 1)
		{
			if (g_label_last)
				g_label_last->new_line += 1;
		}
		if(f == 0)
		{
			if(g_tkn_last)
				g_tkn_last->new_line += 1;
			else if (g_label_last)
				g_label_last->new_line += 1;

		}
		g_data->x++;
		//printf("g->x = %d\n", g_data->x);
	}
}

void	check_dup_label()
{
	t_lbl_lst *tmp;

	tmp = g_label_first;
	if(g_label_first != g_label_last)
	{
		while(tmp != g_label_last)
		{
			if(!ft_strcmp(tmp->label, g_label_last->label))
				error_event(ERR_LABEL_DUB);
			tmp = tmp->next;
		}
	}
}

void	add_lbl(char *s, size_t size)
{
	t_lbl_lst	*new;
	//printf("add_label_s[%zu] =%s\n", size, s);
	if (!(new = (t_lbl_lst *)malloc(sizeof(t_lbl_lst))))
		error_event(ERR_ALLOC);
	new->next = NULL;
	if ((g_tkn_first == NULL && g_label_first == NULL))
	{
		g_label_first = new;
		g_label_last = g_label_first;
		new->offset = 0;
	}
	else if (g_tkn_first == NULL && g_label_first)
	{
		g_label_last->next = new;
		new->offset = g_label_last->offset;
	}
	else
	{
		if (g_label_first == NULL && g_label_last == NULL)
		{
			g_label_first = new;
			g_label_last = g_label_first;
		}
		else
			g_label_last->next = new;
		new->offset = g_tkn_last->offset + g_tkn_last->num_byte_op;
	}
	g_label_last = new;
	g_label_last->label = ft_strsub(s, 0, size);
	check_dup_label();
	/*printf("label_last->label= %s\nlabel_last->offset = %d\n",
	 g_label_last->label, g_label_last->offset);*/
}

static size_t	label_size(char *s)
{
	int	tmp;

	tmp = g_data->x;
	while (s[tmp] && s[tmp] != LABEL_CHAR
	&& s[tmp] != DIRECT_CHAR && !IS_BLANK(s[tmp]))
		++tmp;
	if (s[tmp] == LABEL_CHAR)
		return (tmp - g_data->x);
	return (0);
}

void			check_label(char *line)
{
	size_t		size;

	printf("check_label_%s_line[%d]=%s", line, g_data->x, &(line[g_data->x]));
	if ((size = label_size(line)))
	{
		add_lbl(&(line[g_data->x]), size);
		g_label_last->new_line = 0;
		g_data->x += size + 1;
		printf("check_label_%s_line[%d]=%s", line, g_data->x, &(line[g_data->x]));
		printf("g_data->x =%d\n", g_data->x);
	}

	//t_lbl_lst	*tmp = g_label_first;

//	printf("EXEC_BYTES = %ld(0x%lx)\n", g_data->exec_bytes,g_data->exec_bytes);
/*	while(tmp != NULL)
	{
		printf("label[%d] = |%s| ===>\n",
			tmp->offset, tmp->label);
		tmp = tmp->next;
	}
	printf("\n");*/
	//valid_newline();
	//token_add(END);
}
