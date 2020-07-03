/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/07/03 15:49:31 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		init_refresh(t_vs	*vs)
{
	vs->state_refresh = 1;
	vs->players_refresh = 1;
	vs->carriages_refresh = 1;
	vs->cells_refresh = 1;
}

static t_vs		*t_vs_new(void)
{
	t_vs		*vs;

	if ((vs = (t_vs *)malloc(sizeof(t_vs))))
	{
		init_refresh(vs);
		vs->error_code = 0;
	}	
	return (vs);
}

t_vs			*t_vs_create(t_vm *vm)
{
	t_vs		*new;

	new = NULL;
	new = t_vs_new();
	if (!new)	
		handle_error_vm(ERR_ALLOC, vm);
	vm->allocated += ALLOCATED_VS;
	return (new);
}
