#include "../../includes/com.h"

int		check_reg(char *line, int size, u_int16_t i)
{
	printf("check_reg_line[%d]=%s\n", g_data->x, &(line[g_data->x]));
	if (is_reg(&(line[g_data->x]), size)
			&& g_tkn_last->op->args_types[i] & T_REG)
	{
		g_tkn_last->args[i]->argtype = REGISTER;
		g_tkn_last->args[i]->argsize = 1;
		g_tkn_last->num_byte_op += 1;
/*		printf("REGISTER\nnumbyte_%d\n",
			g_tkn_last->num_byte_op);*/
		return (TRUE);
	}
	return (FALSE);
}

int		check_dir(char *line, int size, u_int16_t i)
{

	if(is_direct(&(line[g_data->x]), size)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args[i]->argtype = DIRECT;
		g_tkn_last->args[i]->argsize = g_tkn_last->op->t_dir_size;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;
//		printf("DIRECT\nnumbyte_%d\n",g_tkn_last->num_byte_op);
		return (TRUE);
	}
	else if(is_dir_label(&(line[g_data->x]), size)
			&& g_tkn_last->op->args_types[i] & T_DIR)
	{
		g_tkn_last->args[i]->argtype = DIRECT_LABEL;
		g_tkn_last->args[i]->argsize = g_tkn_last->op->t_dir_size;
		g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;
/*	printf("DIRECT_LABEL\nnumbyte_%d\n",
		g_tkn_last->num_byte_op);*/
		return (TRUE);
	}
	return (FALSE);
}

int		check_ind(char *line, int size, u_int16_t i)
{
	printf("check_ind_line[%d]=%s\n", g_data->x, &(line[g_data->x]));
	if(is_indirect(&(line[g_data->x]), size)
			&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args[i]->argtype = INDIRECT;
		g_tkn_last->args[i]->argsize = 2;
		g_tkn_last->num_byte_op += 2;
//		printf("INDIRECT\nnumbyte_%d\n", g_tkn_last->num_byte_op);
		return (TRUE);
	}
	else if(is_ind_label(&(line[g_data->x]), size)
		&& g_tkn_last->op->args_types[i] & T_IND)
	{
		g_tkn_last->args[i]->argtype = INDIRECT_LABEL;
		g_tkn_last->args[i]->argsize = 2;
		g_tkn_last->num_byte_op += 2;
//		printf("INDIRECT_LABEL\nnumbyte_%d\n", g_tkn_last->num_byte_op);
		return (TRUE);
	}
	return (FALSE);
}

int		is_emptyline(char *line)
{
	int	i;

	i = 0;
	while(line[i] != '\0')
	{
		if(IS_BLANK(line[i]))
			i++;
		else if(line[i] == '\n')
		{
			g_tkn_last->new_line +=1;
			i++;
		}
		else
			return (0);
	}
	line[0] = '\0';
	return (i);
}

int		is_end_arg(char *line)
{
	int	i;

	i = 0;
	while(line[i] != SEPARATOR_CHAR)
	{
		if (!IS_BLANK(line[i]))
			return(FALSE);
		i++;
	}
	return(TRUE);
}

void	parse_args_type(u_int16_t i, char *line)
{
	int	size;
	int	tab;

	/*printf("----IS_TYPE-----\n");
	printf("0_numbyte_%d\n",g_tkn_last->num_byte_op);*/
	size = 0;
	while(line[g_data->x + size] != SEPARATOR_CHAR
			&& (line[g_data->x + size] != '\n'
				&& line[g_data->x + size] != '\0'))
	{
		if((i == g_tkn_last->op->args_num - 1
			&& (tab = is_emptyline(&(line[g_data->x + size])))))
		{
			break ;
		}
		if(IS_BLANK(line[g_data->x + size]) && is_end_arg(&(line[g_data->x + size])))
			break ;
		size++;
	}
	if (check_reg(line, size, i) || check_dir(line, size, i)
			|| check_ind(line, size, i))
	{
		g_tkn_last->args[i]->arg = ft_strsub(line, g_data->x, size);
		return ;
	}
	else
		put_error(ERR_ARGTP, 1);
}
