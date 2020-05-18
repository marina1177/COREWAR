/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 21:56:47 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static t_vs	*t_vs_new(void)
{
	t_vs	*new;

	if ((new = (t_vs *)malloc(sizeof(t_vs))))
	{
		;
	}
	return (new);
}

t_vs		*t_vs_create(t_vm *vm)
{
	t_vs	*new;

	new = NULL;
	if (!vm->vs)
	{
		new = t_vs_new();
		if (!new)
			handle_error_vm(ERR_ALLOC, vm);
	}
	return (vm->vs ? vm->vs : new);
}
