
#include "com.h"

int	is_reg(char *line, int len)
{
	int	i;
	int	k;

	i = 0;
	if ((len == 2 || len == 3) && line[i++] == 'r')
	{
		while (ft_isdigit(line[i]) && i < len)
			i++;
		k = ft_atoi(&line[1]);
		if (i == (len) && k >= 0)
		{
			if (k > 16)
				ft_putstr("warning: num of reg more 16!\n");
			else if (k == 0)
				error_event(ERR_ZERO_REG);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	is_direct(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == DIRECT_CHAR)
	{
		if (line[1] == '-')
			i++;
		if (line[1] == '+')
			put_error("error - '+' after DIRECT_CHAR", 1);
		while (ft_isdigit(line[i]) && i < len)
			i++;
		if (i == (len))
			return (TRUE);
	}
	return (FALSE);
}

int	is_dir_label(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == DIRECT_CHAR && line[i++] == LABEL_CHAR)
	{
		while (is_lblchar(line[i]) && i < len)
			i++;
		if (i == (len))
			return (TRUE);
	}
	return (FALSE);
}

int	is_indirect(char *line, int len)
{
	int	i;

	i = 0;
	if (line[0] == '-' || line[0] == '+')
		i++;
	while (ft_isdigit(line[i]) && i < len)
		i++;
	if (i == (len))
		return (TRUE);
	return (FALSE);
}

int	is_ind_label(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i++] == LABEL_CHAR)
	{
		while (is_lblchar(line[i]) && i < len)
			i++;
		if (i == (len))
			return (TRUE);
	}
	return (FALSE);
}
