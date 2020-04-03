
#include "com.h"

int32_t	process_label(t_token **tkn, char *label)
{
	int32_t		off;
	t_lbl_lst	*tmp;

	tmp = g_label_first;
	while (*label == LABEL_CHAR || *label == DIRECT_CHAR)
		label++;
	while (tmp)
	{
		if (!(ft_strcmp(label, tmp->label)))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		error();
	off = tmp->offset - ((*tkn)->offset);
	return (off);
}

void	print_args(t_token **tkn, u_int32_t *cursor)
{
	u_int8_t	i;
	u_int8_t	d_size;
	char		*line;

	i = 0;
	while (i < (*tkn)->op->args_num)
	{
		d_size = (*tkn)->op->t_dir_size;
		line = (*tkn)->args[i]->arg;
		if ((*tkn)->args[i]->argtype == REGISTER)
			int_to_hex(ft_atoi_cor(line + 1, 1), 1, cursor);
		else if ((*tkn)->args[i]->argtype == DIRECT)
			int_to_hex(ft_atoi_cor(line + 1, d_size), d_size, cursor);
		else if ((*tkn)->args[i]->argtype == INDIRECT)
			int_to_hex(ft_atoi_cor(line, IND_SIZE), IND_SIZE, cursor);
		else if ((*tkn)->args[i]->argtype == DIRECT_LABEL)
			int_to_hex(process_label(tkn, line), d_size, cursor);
		else if ((*tkn)->args[i]->argtype == INDIRECT_LABEL)
			int_to_hex(process_label(tkn, line), IND_SIZE, cursor);
		i++;
	}
}

void	print_args_types_code(t_token *tkn, u_int32_t *cursor)
{
	u_int8_t	byte;
	u_int8_t	i;
	int			k;
	t_2b		type;

	if (!tkn->op->args_types_code)
		return ;
	byte = 0;
	i = 0;
	k = 3;
	while (i < (tkn)->op->args_num && (type = tkn->args[i]->argtype))
	{
		if (type & REGISTER)
			byte ^= 1 << ((2 * k));
		else if ((type & DIRECT) || (type & DIRECT_LABEL))
			byte ^= 1 << ((2 * k) + 1);
		else if ((type & INDIRECT) || (type & INDIRECT_LABEL))
		{
			byte ^= 1 << ((2 * k));
			byte ^= 1 << ((2 * k) + 1);
		}
		i++;
		k--;
	}
	int_to_hex((int32_t)byte, 1, cursor);
}

void	print_champion_info(void)
{
	ft_memcpy(g_mbuf + 4 + PROG_NAME_LENGTH + 4 * 2,
			g_mdata->head->comment, ft_strlen(g_mdata->head->comment));
	ft_memcpy(g_mbuf + 4, g_mdata->head->prog_name,
		ft_strlen(g_mdata->head->prog_name));
}

void	translate(void)
{
	t_token		*tmp;
	u_int32_t	cursor;

	cursor = 0;
	int_to_hex(COREWAR_EXEC_MAGIC, 4, &cursor);
	print_champion_info();
	cursor = 4 + PROG_NAME_LENGTH + 4;
	int_to_hex(g_mdata->exec_bytes, 4, &cursor);
	cursor = EXEC_START;
	tmp = g_tkn_first;
	while (tmp != NULL)
	{
		int_to_hex(tmp->op->code, 1, &cursor);
		print_args_types_code(tmp, &cursor);
		print_args(&tmp, &cursor);
		tmp = tmp->next;
	}
	size_t size = EXEC_START + g_mdata->exec_bytes;
	if (g_flg & F_OPRINT)
		print_memory((void *)g_mbuf, size);
}
