/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_refresh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:19:26 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 17:19:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		vs_state_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->state_refresh = 1;
	return (1);
}

int		vs_players_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->players_refresh = 1;
	return (1);
}

int		vs_carriages_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->carriages_refresh = 1;
	return (1);
}

int		vs_cells_refresh(t_vm *vm)
{
	if (vm->mods->vs)
		vm->vs->cells_refresh = 1;
	return (1);
}
