/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_put_const.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:38:20 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 17:19:42 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	put_atom_const(t_vm *vm)
{
	vs_putstr_fd(vm->vs->fd, "\n\t\"Consts\": {\n\t\t\"mem_size\": ");
	vs_itoa_fd(vm->vs->fd, MEM_SIZE);
	vs_putstr_fd(vm->vs->fd, A_CYCLEDELTA);
	vs_itoa_fd(vm->vs->fd, CYCLE_DELTA);
	vs_putstr_fd(vm->vs->fd, A_PLAYERS_NUM);
	vs_itoa_fd(vm->vs->fd, vm->players->qty);
	vs_putstr_fd(vm->vs->fd, A_MAXCHECKS);
	vs_itoa_fd(vm->vs->fd, MAX_CHECKS);
	vs_putstr_fd(vm->vs->fd, A_C_NBR_LIVE);
	vs_itoa_fd(vm->vs->fd, NBR_LIVE);
	vs_putstr_fd(vm->vs->fd, A_C_CYCLE_TO_DIE);
	vs_itoa_fd(vm->vs->fd, CYCLE_TO_DIE);
}

void	put_array_const(t_vm *vm)
{
	t_player *tmp;

	vs_putstr_fd(vm->vs->fd, ",\n\t\t\"Players\": [");
	tmp = vm->players->first_player;
	while (tmp)
	{
		vs_putstr_fd(vm->vs->fd, "\n\t\t{");
		vs_putstr_fd(vm->vs->fd, A_C_ID);
		vs_itoa_fd(vm->vs->fd, tmp->num);
		vs_putstr_fd(vm->vs->fd, A_NAME);
		vs_putstr_fd(vm->vs->fd, "\"");
		vs_putstr_fd(vm->vs->fd, tmp->name);
		vs_putstr_fd(vm->vs->fd, "\"");
		vs_putstr_fd(vm->vs->fd, A_START_CODE);
		vs_itoa_fd(vm->vs->fd, tmp->start_code);
		vs_putstr_fd(vm->vs->fd, A_CODE_SIZE);
		vs_itoa_fd(vm->vs->fd, tmp->code_size);
		vs_putstr_fd(vm->vs->fd, "\n\t\t}");
		tmp = tmp->next;
		tmp != NULL ? vs_putstr_fd(vm->vs->fd, ",") : 1;
	}
	vs_putstr_fd(vm->vs->fd, "]\n\t},");
}
