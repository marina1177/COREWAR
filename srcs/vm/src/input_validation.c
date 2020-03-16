#include "../includes/vm.h"



static int	is_valid_flag_n(char *num)
{
	int	number;

	if (!is_integer(num))
		handle_error(sprintf("number after -n (%s) is not integer"));
	number = ft_atoi(num);
	if (number < 1 || number > MAX_PLAYERS)
		handle_error(sprintf("-n argument (%s) must be between \
							 1 and MAX_PLAYERS (op.h defined value)"));	
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
		handle_error(sprintf("-dump argument (%s) must be numeric"));
	return (1);
}

static int	is_valid_player(char *player)
{
	char *s;
	int		fd;

	if ((fd = open(player, O_RDONLY)) == -1)
		handle_error(sprintf("unable to open file %s"));
	return (1);
}

int		is_valid_args(int ac, char **av)
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