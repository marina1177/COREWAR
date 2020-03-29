#include "../../includes/com.h"

int	is_reg(char *line, int len)
{
	int	i;
	int	k;

	i = 0;

	if ((len == 2 || len == 3) && line[i++] == 'r')
	{
		printf("isreg_%s_len = %d_\n", line, len);
		while (ft_isdigit(line[i]) && i < len)
			i++;
		//printf("i=%d\n", i);
		k = ft_atoi(&line[1]);
		//printf("k_atoi = %d\n", k);
		if(i == (len) && (k = ft_atoi(&line[1]) >= 0))
		{
			printf("k_atoi = %d\n",k);
			if (k > 16)
				printf("warning: num of reg more 16!\n");
			else if (k == 0)
			{
				error_event(ERR_ZERO_REG );
			}
			return(TRUE);
		}
	}
	//printf("Syntax error at token [TOKEN][%d:009] INSTRUCTION \"%s\"", g_snum, line);
	return (FALSE);
}

int	is_direct(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == DIRECT_CHAR)
	{
		printf("dir_%s__len = %d\n",&(line[i]), len);
		if (line[1] == '-')
		{
			i++;
		}
		if (line[1] == '+')
		{
			printf("error - '+' after DIRECT_CHAR\n");
			printf("Lexical error at [5:9]");

			error();
		}
		while (ft_isdigit(line[i]) && i < len)
			i++;
		//printf("i = %d\n",i);
		if(i == (len))
			return(1);
	}
	return (0);
}

int	is_dir_label(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == DIRECT_CHAR && line[i++] == LABEL_CHAR)
	{
		printf("dir_label_%s\n",&(line[i]));
		while (is_lblchar(line[i]) && i < len)
			i++;
		if(i == (len))
			return(1);
	}
	return (0);
}

int	is_indirect(char *line, int len)
{
	int	i;

	i = 0;
	printf("is_indirect_%s\n",&(line[i]));
	while (ft_isdigit(line[i]) && i < len)
		i++;
	if(i == (len))
		return(1);
	return(0);
}

int	is_ind_label(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == LABEL_CHAR)
	{
		printf("ind_label_%s\n",&(line[i]));
		while (is_lblchar(line[i]) && i < len)
			i++;
		if(i == (len))
			return(1);
	}
	return (0);
}
