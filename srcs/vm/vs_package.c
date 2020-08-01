/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_package.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:21:41 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 17:19:33 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	put_file(t_vm *vm, int type)
{
	type == 0 ? vs_putstr_fd(vm->vs->fd, "[{") :
	vs_putstr_fd(vm->vs->fd, ",{");
	if (type == 0)
	{
		put_atom_const(vm);
		put_array_const(vm);
	}
	vs_putstr_fd(vm->vs->fd, A_CYCLE);
	vs_itoa_fd(vm->vs->fd, vm->data->cycles);
	if (put_state(vm) == 0)
	{
		return ;
	}
	put_players(vm);
	put_carriages(vm);
	put_cells(vm);
	type == 2 ? vs_putstr_fd(vm->vs->fd, "\n}]")
	: vs_putstr_fd(vm->vs->fd, "\n}");
}

void	clean_refresh(t_vm *vm)
{
	vm->vs->state_refresh = 0;
	vm->vs->players_refresh = 0;
	vm->vs->carriages_refresh = 0;
	vm->vs->cells_refresh = 0;
}

void	clean_cells(t_vm *vm)
{
	t_cells	*tmp;

	tmp = vm->cells;
	while (tmp)
	{
		tmp->num_addr = -1;
		tmp = tmp->next;
	}
}

int		print_vsconst(t_vm *vm, int type)
{
	if (!vm->mods->vs)
		return (0);
	if (type == 0 &&
	(vm->vs->fd = open("vis.json", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
	{
		ft_dprintf(vm->vs->fd, "%s\n", "vis.json file error\n");
		return (0);
	}
	if (vm->vs->fd > 0)
	{
		put_file(vm, type);
		clean_refresh(vm);
		clean_cells(vm);
		if (type == 2)
		{
			write(vm->vs->fd, "]", 1);
			close(vm->vs->fd);
			return (1);
		}
	}
	return (1);
}
