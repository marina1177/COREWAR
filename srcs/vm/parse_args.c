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

static int	is_valid_flag_n(t_vm *vm, char *num)
{
	int		number;

	if (!is_integer(num))
		handle_error_str_arg(ERR_NOINT, num, vm);
	number = ft_atoi(num);
	if (number < 1 || number > MAX_PLAYERS)
		handle_error_str_arg(ERR_N_FLAG, num, vm);
	if (!is_number_unique(vm, number))
		return (0);
	return (number);
}

static int	parse_flag_dump(t_vm *vm, char *num)
{
	int		number;

	if (!is_integer(num))
		handle_error_str_arg(ERR_NOINT, num, vm);
	number = ft_atoi(num);
	if (number < 0)
		handle_error_str_arg(ERR_D_FLAG, num, vm);
	vm->mods->dump_print_mode = 1;
	vm->mods->dump_cycle = number;
	return (1);
}

void	parse_args(t_vm *vm, int ac, char **av)
{
	int	i;
	int number;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			number = is_valid_flag_n(vm, av[++i]);
			parse_player(vm, av[++i],
			t_players_add_new_player(vm->players, number, vm));
			
		}
		else if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d"))
			parse_flag_dump(vm, av[i + 1]);
		else if (!ft_strcmp(av[i], "-v"))
			vm->vs = t_vs_create(vm);
		else
		{
			parse_player(vm, av[i],
			t_players_add_new_player(vm->players, 0, vm));
		}
	}
	handle_players(vm, vm->players);
}