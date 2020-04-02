#include "../../includes/com.h"

int valid_register(int i)
{
	char *line;

	line = skip_space(g_tkn_last->op_args[i]);
	if (is_reg(line)
			&& g_tkn_last->op->args_types[i] & T_REG)
	{
		g_tkn_last->args_type[i] = REGISTER;
		g_tkn_last->num_byte_op += 1;

		printf("REGISTER\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		return (TRUE);
	}
	return (FALSE);
}

int check_dir(int i)
{
	char *line;

	line = skip_space(g_tkn_last->op_args[i]);
	if(is_direct(line)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args_type[i] = DIRECT;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;

		printf("DIRECT\nnumbyte_%d\n",g_tkn_last->num_byte_op);
		return (TRUE);
	}
	else if(is_dir_label(line)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args_type[i] = DIRECT_LABEL;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;

		printf("DIRECT_LABEL\nnumbyte_%d\n",
		g_tkn_last->num_byte_op);
		return (TRUE);
	}
	return (FALSE);
}

int check_ind(int i)
{
	char *line;

	line = skip_space(g_tkn_last->op_args[i]);
	if(is_indirect(line)
			&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args_type[i] = INDIRECT;
		g_tkn_last->num_byte_op += IND_CODE;

		printf("INDIRECT\nnumbyte_%d\n", g_tkn_last->num_byte_op);
		return (TRUE);
	}
	else if(is_ind_label(line)
		&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args_type[i] = INDIRECT_LABEL;
		g_tkn_last->num_byte_op += IND_CODE;

		printf("INDIRECT_LABEL\nnumbyte_%d\n", g_tkn_last->num_byte_op);
		return (TRUE);
	}
	return (FALSE);
}

void	parse_args_type()
{
	int i;

	i = -1;
	printf("----IS_TYPE-----\n");

	g_tkn_last->num_byte_op = 1;
	if (g_tkn_last->op->args_types_code)
		g_tkn_last->num_byte_op += 1;
	printf("0_numbyte_%d\n",
			g_tkn_last->num_byte_op);
	while (g_tkn_last->op_args[++i] != NULL)
	{
		printf("lex[%d] = %s - ", i, g_tkn_last->op_args[i]);

		if(valid_register(i))
		{
			printf("is_reg_%s\n",g_tkn_last->op_args[i]);
			continue ;
		}
		else if(check_dir(i))
		{
			printf("is_dir_%s\n",g_tkn_last->op_args[i]);
			continue ;
		}
		else if(check_ind(i))
			continue ;
		else
		{
			//printf("Syntax error at token [TOKEN][%d:009] INSTRUCTION \"%s\"", g_snum, g_tkn_last->op_args[i]);
			error_event(ERR_ARGTP);
		}
		//i++;
	}
	printf("tkn_offset = %d\ntkn_numbyte = %d\n", g_tkn_last->offset,
			g_tkn_last->num_byte_op);
}
