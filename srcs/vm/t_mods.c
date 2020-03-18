/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 17:23:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

t_vs *t_mods_new(void)
{
	t_mods	*new;

	if ((new = (t_mods *)malloc(sizeof(t_mods))))
	{
		new->dump_cycle = 0;
		new->dump_print_mode = 0;
		new->show_cycle = 0;
		new->show_print_mode = 0;
		new->display_aff = false;
		new->log = 0;
	}
	return (new);
}

t_vm *t_vm_create(void)
{
	t_vm	*new;
	int		i;

	i = -1;
	new = NULL;
	if (is_valid_op_h())
	{
		new = t_vm_new();
		
	}
	return (new);
}



