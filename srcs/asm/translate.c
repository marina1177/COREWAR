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
	u_int8_t	i;
	int			k;
	t_2b		type;

	printf("print_args_types_code\n");

	if (!tkn->op->args_types_code)
		return ;
	byte = 0;
	i = 0;
	k = 3;
	while (i < (tkn)->op->args_num && (type = tkn->args[i]->argtype))
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
	printf("process label_%s\n", label);

	int32_t		off;
	t_lbl_lst	*tmp;

	tmp = g_label_first;
	while(*label == LABEL_CHAR || *label == DIRECT_CHAR)
		label++;
	while (tmp)
	{
		//printf("%s__vs__%s\n", label, tmp->label);
		if (!(ft_strcmp(label, tmp->label)))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error();
	}
	off = tmp->offset - ((*tkn)->offset);
	printf("%s_offset = %d___%s_offset = %d\n", tmp->label,tmp->offset,((*tkn)->op->name),((*tkn)->offset));
	printf("offset label = %d\n", off);
	return (off);
}

void	print_args(t_token **tkn, u_int32_t *cursor)
{
	u_int8_t	i;
	u_int8_t	d_size;
	char		*line;

	printf("print_args\n");
	i = 0;
	while (i < (*tkn)->op->args_num)
	{
		d_size = (*tkn)->op->t_dir_size;
		line = (*tkn)->args[i]->arg;

		if ((*tkn)->args[i]->argtype == REGISTER)
		{
			printf("reg = |%s|\n", (*tkn)->args[i]->arg + 1);
			int_to_hex(ft_atoi_cor(line + 1, 1), 1, cursor);//+ 'r'

		}
		else if ((*tkn)->args[i]->argtype == DIRECT)
		{
			printf("dir = !%s!\n", (*tkn)->args[i]->arg + 1);
			int_to_hex(ft_atoi_cor(line + 1, d_size), d_size, cursor);//+ '%'
		}
		else if ((*tkn)->args[i]->argtype == INDIRECT)
			int_to_hex(ft_atoi_cor(line, IND_SIZE), IND_SIZE, cursor);

		else if ((*tkn)->args[i]->argtype == DIRECT_LABEL)
		{
			printf("dir_lbl = %d\n", process_label(tkn, line));
			int_to_hex(process_label(tkn, line), d_size, cursor);
		}
		else if ((*tkn)->args[i]->argtype == INDIRECT_LABEL)
			int_to_hex(process_label(tkn, line), IND_SIZE, cursor);

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
	int_to_hex(g_data->exec_bytes, 4, &cursor);
	cursor = EXEC_START;
//	printf("EXEC_START\n");
	tmp = g_tkn_first;
	while (tmp != NULL)
	{
		//printf("tmp_instr = %s\n", tmp->op->name);
		/*unsigned int i = 0;
		while(i < (tmp)->op->args_num)
		{
			if(tmp->args[i]->argtype == REGISTER)
				printf("%s - REGISTER\n",tmp->args[i]->arg);
			else if(tmp->args[i]->argtype == DIRECT || tmp->args[i]->argtype == DIRECT_LABEL)
				printf("%s - DIRECT\n",tmp->args[i]->arg);
			else if(tmp->args[i]->argtype == INDIRECT || tmp->args[i]->argtype == INDIRECT_LABEL)
				printf("%s - INDIRECT\n",tmp->args[i]->arg);
			i++;
		}*/
	//	printf("code operation(%d):\n", tmp->op->code);
		int_to_hex(tmp->op->code, 1, &cursor);
	//	printf("args_types_code:\n");
		print_args_types_code(tmp, &cursor);
//		printf("************ARGS*************:\n");
		print_args(&tmp, &cursor);
	//	printf("*****************************:\n");
		tmp = tmp->next;
	}
	size_t size = EXEC_START + g_data->exec_bytes;
	//print_bits(size,(void *)g_buf, 1);
	print_memory((void *)g_buf, size);
}
