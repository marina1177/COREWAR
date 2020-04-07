/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static t_vs	*t_vs_new(void)
{
	t_vs	*new;

	if ((new = (t_vs *)malloc(sizeof(t_vs))))
	{

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