/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_refresh_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:57:43 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 17:19:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		vs_reset_refresh(t_vm *vm)
{
	t_cells *temp;

	if (vm->mods->vs)
	{
		temp = vm->cells;
		while (temp)
		{
			temp->num_addr = -1;
			temp = temp->next;
		}
		vm->vs->cells_refresh = 0;
		vm->vs->carriages_refresh = 0;
		vm->vs->players_refresh = 0;
		vm->vs->state_refresh = 0;
	}
	return (1);
}
