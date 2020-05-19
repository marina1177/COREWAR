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
	vm->exec[1] = do_live;
	vm->exec[2] = do_ld;
	vm->exec[3] = do_st;
	vm->exec[4] = do_add;
	vm->exec[5] = do_sub;
	vm->exec[6] = do_and;
	vm->exec[7] = do_or;
	vm->exec[8] = do_xor;
	vm->exec[9] = do_zjmp;
	vm->exec[10] = do_ldi;
	vm->exec[11] = do_sti;
	vm->exec[12] = do_fork;
	vm->exec[13] = do_lld;
	vm->exec[14] = do_lldi;
	vm->exec[15] = do_lfork;
	vm->exec[16] = do_aff;
}

static t_vm	*t_vm_new(void)
{
	t_vm	*vm;
	int		i;

	!(vm = (t_vm *)malloc(sizeof(t_vm))) ? handle_error(ERR_ALLOC) : 0;
	!(vm->players = t_players_new()) ? handle_error_vm(ERR_ALLOC, vm) : 0;
	!(vm->vs = (t_vs *)malloc(sizeof(t_vs))) ?
		handle_error_vm(ERR_ALLOC, vm) : 0;
	vm->data = t_vm_info_create(vm);
	vm->carr = t_carriages_create(vm);
	vm->mods = t_mods_create(vm);
	i = -1;
	while (++i < REG_NUMBER + 1)
		vm->op_tab[i] = g_op_tab[i];
	init_exec(vm);
	return (vm);
}

t_vm		*t_vm_create(void)
{
	t_vm	*new;

	new = NULL;
	if (is_valid_op_h())
	{
		new = t_vm_new();
	}
	return (new);
}



