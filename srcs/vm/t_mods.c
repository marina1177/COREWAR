/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mods.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_mods *t_mods_new(void)
{
	t_mods	*new;

	if ((new = (t_mods *)malloc(sizeof(t_mods))))
	{
		new->dump_cycle = -1;
		new->dump_size = 0;
		new->show_cycle = 0;
		new->show_print_mode = 0;
		new->aff = false;
		new->log = 0;
	}
	return (new);
}

t_mods *t_mods_create(t_vm *vm)
{
	t_mods	*new;

	new = t_mods_new();
	if (!new)
		handle_error_vm(ERR_ALLOC, vm);
	return (new);
}



