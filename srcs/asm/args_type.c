#include "../../includes/com.h"

void	parse_args_type()
{
	int i;

	i = 0;
	printf("----IS_TYPE-----\n");

	g_tkn_last->num_byte_op = 1;
	if (g_tkn_last->op->args_types_code)
		g_tkn_last->num_byte_op += 1;
	printf("0_numbyte_%d\n",
			g_tkn_last->num_byte_op);
	while (g_tkn_last->op_args[i] != NULL)
	{
		printf("lex[%d] = %s - ", i, g_tkn_last->op_args[i]);
		if (is_reg(g_tkn_last->op_args[i])
			&& g_tkn_last->op->args_types[i] & T_REG)
		{
			g_tkn_last->args_type[i] = REGISTER;
			g_tkn_last->num_byte_op += REG_CODE;

			printf("REGISTER\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		}
		else if(is_direct(g_tkn_last->op_args[i])
			&& g_tkn_last->op->args_types[i] & T_DIR)
		{
			g_tkn_last->args_type[i] = DIRECT;
			g_tkn_last->num_byte_op += DIR_CODE;

			printf("DIRECT\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		}
		else if(is_dir_label(g_tkn_last->op_args[i])
			&& g_tkn_last->op->args_types[i] & T_DIR)
		{
			g_tkn_last->args_type[i] = DIRECT_LABEL;
			g_tkn_last->num_byte_op += DIR_CODE;

			printf("DIRECT_LABEL\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		}
		else if(is_indirect(g_tkn_last->op_args[i])
			&& g_tkn_last->op->args_types[i] & T_IND)
		{
			g_tkn_last->args_type[i] = INDIRECT;
			g_tkn_last->num_byte_op += IND_CODE;

			printf("INDIRECT\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		}
		else if(is_ind_label(g_tkn_last->op_args[i])
			&& g_tkn_last->op->args_types[i] & T_IND)
		{
			g_tkn_last->args_type[i] = INDIRECT_LABEL;
			g_tkn_last->num_byte_op += IND_CODE;

			printf("INDIRECT_LABEL\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);
		}
		else
		{
			error_event(ERR_ARGTP);
			/*printf("argument type error\n");
			error();*/
		}
		i++;
	}
	printf("tkn_offset = %d\ntkn_numbyte = %d\n", g_tkn_last->offset,
			g_tkn_last->num_byte_op);
}
