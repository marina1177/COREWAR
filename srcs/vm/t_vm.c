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

static int	is_valid_op_h(void)
{
	return (1);
}

static void	init_exec(t_vm *vm)
{
	vm->exec[0] = 0;
	vm->exec[1] = live;
	vm->exec[2] = ld;
	vm->exec[3] = st;
	vm->exec[4] = add;
	vm->exec[5] = sub;
	vm->exec[6] = and;
	vm->exec[7] = or;
	vm->exec[8] = xor;
	vm->exec[9] = zjmp;
	vm->exec[10] = ldi;
	vm->exec[11] = sti;
	vm->exec[12] = cwfork;
	vm->exec[13] = lld;
	vm->exec[14] = lldi;
	vm->exec[15] = lfork;
	vm->exec[16] = aff;
}

static t_vm *t_vm_new(void)
{
	t_vm	*vm;

	!(vm = (t_vm *)malloc(sizeof(t_vm))) ? handle_error("Malloc error") : 0;	
	!(vm->data = t_vm_info_new()) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->players = t_players_new()) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->carr = t_carriages_new()) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->vs = (t_vs *)malloc(sizeof(t_vs))) ? handle_error_vm("Malloc error", vm) : 0;
	!(vm->mods = t_mods_create(vm)) ? handle_error_vm("Malloc error", vm) : 0;
	init_exec(vm);

	return	(vm);
}

t_vm *t_vm_create(void)
{
	t_vm	*new;

	new = NULL;
	if (is_valid_op_h())
	{
		new = t_vm_new();		
	}
	return (new);
}



