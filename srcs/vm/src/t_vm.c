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

#include "../includes/vm.h"

static int	is_valid_op_h(void)
{
	return (1);
}

static t_vm *t_vm_new(void)
{
	t_vm	*vm;

	!(vm = (t_vm *)malloc(sizeof(t_vm))) ? handle_error("Malloc error") : 0;
	!(vm->data = (t_data *)malloc(sizeof(t_data))) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->players = t_players_new();	
	!(vm->carr = (t_carr *)malloc(sizeof(t_carr))) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->vs = (t_vs *)malloc(sizeof(t_vs))) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->mods = (t_mods *)malloc(sizeof(t_mods))) ? handle_error_vm("Malloc error", vm) : 0;
	return	(vm);
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



