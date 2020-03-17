#include "../includes/vm.h"

static int	is_integer(char *s)
{
	size_t	len;
	int		n;

	n = ft_atoi(s);
	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || (int)len != ft_ilen(n))
		return (0);
	if (s[0] == '-' && len == 1)
		return (0);
	return (1);
}

static int	is_valid_flag_dump(char *num)
{
	//нет верхней границы значения dump, как оценить?
	int	number;

	if (!is_integer(num))
		handle_error(sprintf("number after -n (%s) is not integer"));
	number = ft_atoi(num);
	if (number < 0)
		handle_error(sprintf("-dump argument (%s) must be equal or more tham 0"));
	return (1);
}

static int is_valid_op_h_constants(void)
{
	//check all op_h constants
	return (1);
}

int		is_valid_input(int ac, char **av)
{
	int	i;

	i = 1;		
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
			is_valid_flag_n(av[++i]);
		else if (!ft_strcmp(av[i], "-dump"))
			is_valid_flag_dump(av[++i]);
		else if (ft_strcmp(av[i], "-v"))
			is_valid_players(av[i]);
		i++;
	}
	return (1);
}