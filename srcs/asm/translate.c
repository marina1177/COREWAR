#include "../../includes/com.h"

void	int_to_hex(int32_t dec, int dir_size, u_int32_t *place)
{
	int			move;
	int			buf;

	printf(">>_int_to_hex_>> __%d\n", dec);
	buf = dir_size;
	move = 0;
	u_int8_t tmp;
	while (dir_size)
	{
		tmp = (u_int8_t)((dec >> move) & 0xFF);
		//printf("hex = %c = %d = 0x%x\n", tmp, (int)tmp, tmp);
		g_buf[*place + dir_size - 1] = tmp;
		move += 8;
		dir_size--;
	}
	*place += buf;
}

void	print_champion_info()
{
	printf("print_champion_info\n");

	ft_memcpy(g_buf + 4 + PROG_NAME_LENGTH + 4 * 2,
			g_data->head->comment, ft_strlen(g_data->head->comment));
	ft_memcpy(g_buf + 4, g_data->head->prog_name,
		ft_strlen( g_data->head->prog_name));
}

void	print_args_types_code(t_token *tkn, u_int32_t *cursor)
{
	u_int8_t	byte;
	int			i;
	int			k;
	t_2b		type;

	printf("print_args_types_code\n");

	if (!tkn->op->args_types_code)
		return ;
	byte = 0;
	i = 0;
	k = (tkn)->op->args_num;
	while ((type = tkn->args_type[i]) && k > 0)
	{
		if (type & REGISTER)
		{
			byte ^= 1 << ((2 * k));
		}
		else if ((type & DIRECT) || (type & DIRECT_LABEL))
		{
			byte ^= 1 << ((2 * k) + 1);
		}
		else if ((type & INDIRECT) || (type & INDIRECT_LABEL))
		{
			byte ^= 1 << ((2 * k));
			byte ^= 1 << ((2 * k) + 1);
		}
		printf("byte__:\n");print_bits(1, &byte, 0);//printf("\n");
		printf("hex_byte = 0x%x\n", byte);
		i++;
		k--;
	}
	int_to_hex((int32_t)byte, 1, cursor);
}

int32_t	process_label(t_token **tkn, char *label)
{
	int32_t		off;
	t_lbl_lst	*tmp;

	tmp = g_label_first;
	while (tmp)
	{
		if ((ft_strcmp(label, tmp->label)))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		printf("ERR_LABEL_EX!! -- <<add token x/y>>\n");
		error();
	}
	off = tmp->offset - ((*tkn)->offset);
	return (off);
}

void	print_args(t_token **tkn, u_int32_t *cursor)
{
	u_int8_t	i;
	u_int8_t	d_size;

	printf("print_args\n");

	i = 0;
	while (i < (*tkn)->op->args_num)
	{
		d_size = (*tkn)->op->t_dir_size;
		if ((*tkn)->args_type[i] == REGISTER)
		{
			printf("reg = %s\n", (*tkn)->op_args[i] + 1);
			int_to_hex(ft_atoi_cor((*tkn)->op_args[i] + 1, 1), 1, cursor);//+ 'r'

		}

		else if ((*tkn)->args_type[i] == DIRECT)
		{
			printf("dir = %s\n", (*tkn)->op_args[i]);
			int_to_hex(ft_atoi_cor((*tkn)->op_args[i] + 1, d_size), d_size, cursor);//+ '%'
		}
		else if ((*tkn)->args_type[i] == INDIRECT)
			int_to_hex(ft_atoi_cor((*tkn)->op_args[i], IND_SIZE), IND_SIZE, cursor);

		else if ((*tkn)->args_type[i] == DIRECT_LABEL)
		{
			printf("dir_lbl = %d\n", process_label(tkn, (*tkn)->op_args[i]));
			int_to_hex(process_label(tkn, (*tkn)->op_args[i]), d_size, cursor);
		}

		else if ((*tkn)->args_type[i] == INDIRECT_LABEL)
			int_to_hex(process_label(tkn, (*tkn)->op_args[i]), IND_SIZE, cursor);

		i++;
	}
}

void	translate(void)
{
	t_token		*tmp;
	u_int32_t	cursor;

	cursor = 0;
	int_to_hex(COREWAR_EXEC_MAGIC, 4, &cursor);

	print_champion_info();

	cursor = 4 + PROG_NAME_LENGTH + 4;
	printf("exec_bytes(%llu):\n", g_data->exec_bytes);
	int_to_hex(g_data->exec_bytes, 4, &cursor);
	cursor = EXEC_START;
	printf("EXEC_START\n");

	tmp = g_tkn_first;
	while (tmp != g_tkn_last)
	{
		printf("tmp_instr = %s\n", tmp->op->name);
		unsigned int i = 0;
		while(i < (tmp)->op->args_num)
		{
			if(tmp->args_type[i] == REGISTER)
				printf("%s - REGISTER\n",tmp->op_args[i]);
			else if(tmp->args_type[i] == DIRECT || tmp->args_type[i] == DIRECT_LABEL)
				printf("%s - DIRECT\n",tmp->op_args[i]);
			else if(tmp->args_type[i] == INDIRECT || tmp->args_type[i] == INDIRECT_LABEL)
				printf("%s - INDIRECT\n",tmp->op_args[i]);
			i++;
		}
		printf("code operation(%d):\n", tmp->op->code);
		int_to_hex(tmp->op->code, 1, &cursor);

		printf("args_types_code:\n");
		print_args_types_code(tmp, &cursor);

		printf("************ARGS*************:\n");
		print_args(&tmp, &cursor);
		printf("*****************************:\n");
		tmp = tmp->next;
	}
}
