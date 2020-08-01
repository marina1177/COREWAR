/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_refresh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:19:26 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 16:25:53 by bcharity         ###   ########.fr       */
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
