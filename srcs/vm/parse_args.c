#include "../../includes/vm.h"

static int	is_number_unique(t_vm *vm, int number)
{
	t_player *temp;

	temp = vm->players->first_player;
	while (temp)
	{
		if (temp->num == number)
			handle_error_int_arg(ERR_N_DUPL, number, vm);
		temp = temp->next;
	}
	return (1);
}

static int	is_valid_flag_n(t_vm *vm, int ac, char **av, int i)
{
	int		number;
	char	*num;

	ac == i ? handle_error_vm(ERR_NONUM, vm) : 0;
	num = av[i];
	if (!is_integer(num))
		handle_error_str_arg(ERR_NOINT, num, vm);
	number = ft_atoi(num);
	if (number < 1 || number > MAX_PLAYERS)
		handle_error_str_arg(ERR_N_FLAG, num, vm);
	if (!is_number_unique(vm, number))
		return (0);
	return (number);
}

static int	parse_flag_dump(t_vm *vm, int ac, char **av, int i)
{
	int		number;
	char	*num;
	char	*arg;

	arg = av[++i - 1];
	i == ac ? handle_error_vm(ERR_NONUM, vm) : 0;
	num = av[i];
	if (!is_integer(num))
		handle_error_str_arg(ERR_NOINT, num, vm);
	number = ft_atoi(num);
	if (number < 0)
		handle_error_str_arg(ERR_D_FLAG, num, vm);	
	vm->mods->dump_size = !ft_strcmp(arg, "-d") ? 64 : 32;
	if (g_el)
		vm->mods->dump_size = vm->mods->dump_size == 32 ? 64 : 32;
	vm->mods->dump_cycle = number;
	return (1);
}

static int	parse_flag_v(t_vm *vm, int ac, char **av, int i)
{
	int		number;
	char	*num;
	
	++i == ac ? handle_error_vm(ERR_NONUM, vm) : 0;
	num = av[i];
	if (!is_integer(num))
		handle_error_str_arg(ERR_NOINT, num, vm);
	number = ft_atoi(num);
	if (number < 0 || number > 31)
		handle_error_str_arg(ERR_D_FLAG, num, vm);	
	vm->mods->verbosity_level = number;	
	return (1);
}

void		parse_args(t_vm *vm, int ac, char **av)
{
	int		i;
	int		number;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			number = is_valid_flag_n(vm, ac, av, ++i);
			i + 1 == ac ? handle_error_vm(ERR_NOPLR, vm) : 0;
			parse_player(vm, av[++i], t_players_add(vm->players, number, vm));
		}
		else if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d"))
			parse_flag_dump(vm, ac, av, i++);
		else if (!ft_strcmp(av[i], "-v"))
			parse_flag_v(vm, ac, av, i++);
		else if (!ft_strcmp(av[i], "-el"))		
			g_el = 1;
		else if (!ft_strcmp(av[i], "-a"))
			vm->mods->aff = 1;		
		else
			parse_player(vm, av[i], t_players_add(vm->players, 0, vm));
	}
	handle_players(vm, vm->players);
}