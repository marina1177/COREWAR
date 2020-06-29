/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/06/29 15:11:04 by bcharity         ###   ########.fr       */
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

static t_vs		*t_vs_new(t_vm *vm)
{
	t_vs		*vs;

	if ((vs = (t_vs *)malloc(sizeof(t_vs))))
	{
		init_refresh(vs);
		vs->error_code = 0;
	}
	else
	{
		handle_error_vm(ERR_ALLOC, vm);
	}
	return (vs);
}

t_vs			*t_vs_create(t_vm *vm)
{
	t_vs		*new;

	new = NULL;
	new = t_vs_new(vm);
	return (new);
}
