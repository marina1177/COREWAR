/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 18:04:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	is_number_unique(t_vm *vm, int number)
{
	t_player *temp;

	temp = vm->players->first_player;
	while (temp)
	{
		if (temp->num == number)
			handle_error_vm("Ambiguous player number for %s", vm);
		temp = temp->next;
	}
}

static int	is_valid_flag_n(t_vm *vm, char *num)
{
	int	number;

	if (!is_integer(num))
		handle_error(sprintf("number after -n (%s) is not integer"));
	number = ft_atoi(num);
	if (number < 1 || number > MAX_PLAYERS)
		handle_error(sprintf("-n argument (%s) must be in range \
							 [1, MAX_PLAYERS] (op.h defined value)"));
	!is_number_unique ? 1 : 0;	
	return (number);
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
			if (is_valid_player(vm, av[++i]))
				t_players_add_new_player(vm->players, number, vm);
		}
		else if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d"))
			parse_flag_dump(i + 1, ac, av, vm);
		else
			parse_player(vm, av[i]);
		i++;
	}
}

int     main(int ac, char **av)
{
	t_vm	*vm;

	ac < 2 ? print_usage() : 0;	
	vm = t_vm_create();
	parse_args(vm, ac, av);
	
	return (0);
}