#include "../../includes/com.h"

void	int_to_hex(int32_t dec, int dir_size, u_int32_t *place)
{
	int			move;
	int			buf;

	buf = dir_size;
	move = 0;
	u_int8_t tmp;
	while (dir_size)
	{
		tmp = (u_int8_t)((dec >> move) & 0xFF);
		printf("hex = %c = %d\n", tmp, (int)tmp);
		g_buf[*place + dir_size - 1] = tmp;
		move += 8;
		dir_size--;
	}
	*place += buf;
}

t_token		*print_champion_info()
{

	ft_memcpy(g_buf + 4 + PROG_NAME_LENGTH + 4 * 2,
			g_data->head->comment, ft_strlen(g_data->head->comment));
	ft_memcpy(g_buf + 4, g_data->head->prog_name,
		ft_strlen( g_data->head->prog_name));
}

void	print_args(t_token **op, u_int32_t *cursor, u_int8_t type)
{
	u_int8_t n_arg;
	u_int8_t d_size;

	int_to_hex(g_op_tab[type].code, 1, cursor);
	n_arg = g_op_tab[type].args_num;
	if (g_op_tab[type].args_types_code)
		arg_types_code(*op, cursor, n_arg);
	*op = (*op)->prev;
	while (n_arg--)
	{
		d_size = g_op_tab[type].t_dir_size;
		if ((*op)->type == REGISTER)
			int_to_hex(ft_atoi_cor((*op)->content + 1, 1), 1, cursor);

		else if ((*op)->type == DIRECT)
			int_to_hex(ft_atoi_cor((*op)->content, d_size), d_size, cursor);
		else if ((*op)->type == INDIRECT)
			int_to_hex(ft_atoi_cor((*op)->content, IND_SIZE), IND_SIZE, cursor);

		else if ((*op)->type == DIRECT_LABEL)
			int_to_hex(process_label((*op)->bytes, *op), d_size, cursor);
		else if ((*op)->type == INDIRECT_LABEL)
			int_to_hex(process_label((*op)->bytes, *op), IND_SIZE, cursor);
		*op = (*op)->prev;
	}
}

void	print_args_types_code(t_token *tkn, u_int32_t *cursor)
{
	u_int8_t	byte;
	int			i;
	t_2b		type;

	if (!tkn->op->arg_types_code)
		return ;
	byte = 0;
	i = 0;
	while ((type = tkn->args_type[i]))
	{
		if (type & REGISTER)
		{
			byte ^= 1 << ((2 * i) + 1);
		}
		else if ((type & DIRECT) || (type & DIRECT_LABEL))
		{
			byte ^= 1 << ((2 * i));
		}
		else if ((type & INDIRECT) || (type & IND_LABEL))
		{
			byte ^= 1 << ((2 * i));
			byte ^= 1 << ((2 * i) + 1);
		}
		printf("byte__");print_bits(1, &byte, 0);printf("\n");
		i++;
	}
	int_to_hex((int32_t)byte, 1, cursor);

}

void	translate(void)
{
	t_token		*tmp;
	u_int32_t	cursor;

	cursor = 0;
	int_to_hex(COREWAR_EXEC_MAGIC, 4, &cursor);
	print_champion_info(g_data->head);
	cursor = 4 + PROG_NAME_LENGTH + 4;
	int_to_hex(g_data->exec_bytes, 4, &cursor);
	cursor = EXEC_START;

	tmp = g_tkn_first;
	while (tmp != g_tkn_last)
	{
		print_args_types_code(tmp, &cursor);
		//fill_args()
		print_args(&tmp, &cursor, tmp->op->);
		tmp = tmp->next;
	}
}
