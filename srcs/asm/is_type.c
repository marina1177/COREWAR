#include "../../includes/com.h"

int	is_reg(char *line)
{
	int	i;
	int	k;
	int len;

	i = 0;
	len = ft_strlen(line);
	if ((2 == len || len == 3) && line[i++] == 'r')
	{
		while (ft_isdigit(line[i]) && i < len)
			i++;
		//return (i == len && ft_atoi(&line[1]) > 0);
		if(i == (len) && (k = ft_atoi(&line[1]) >= 0))
		{
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

int	is_direct(char *line)
{
	int	i;
	int	len;

	i = 0;
	if (line[i++] == DIRECT_CHAR)
	{
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
		len = ft_strlen(&(line[i]));
		while (ft_isdigit(line[i]) && i < len)
			i++;
		if(i == (len))
			return(1);
	}
	return (0);
}

int	is_dir_label(char *line)
{
	int	i;
	int	len;

	i = 0;
	if (line[i++] == DIRECT_CHAR && line[i++] == LABEL_CHAR)
	{
		len = ft_strlen(&(line[i]));
		while (is_lblchar(line[i]) && i < len)
			i++;
		if(i == (len))
			return(1);
	}
	return (0);
}

int	is_indirect(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (ft_isdigit(line[i]) && i < len)
		i++;
	if(i == (len))
		return(1);
	return(0);
}

int	is_ind_label(char *line)
{
	int	i;
	int	len;

	i = 0;
	if (line[i++] == LABEL_CHAR)
	{
		len = ft_strlen(&(line[i]));
		while (is_lblchar(line[i]) && i < len)
			i++;
		if(i == (len))
			return(1);
	}
	return (0);
}
