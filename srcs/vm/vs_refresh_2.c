/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_refresh_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:57:43 by bcharity          #+#    #+#             */
/*   Updated: 2020/08/01 16:57:57 by bcharity         ###   ########.fr       */
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
