/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 21:56:47 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	is_valid_op_h(void)
{
	if (IND_SIZE != 2 || REG_SIZE != 4 || DIR_SIZE != REG_SIZE
		|| REG_CODE != 1 || DIR_CODE != 2 || IND_CODE != 3
		|| MAX_ARGS_NUMBER != 4
		|| MAX_PLAYERS > 4 || MAX_PLAYERS < 1
		|| MEM_SIZE < 1024 || MEM_SIZE >= 0xffff
		|| IDX_MOD != MEM_SIZE / 8
		|| CHAMP_MAX_SIZE != MEM_SIZE / 6
		|| REG_NUMBER != 16
		|| CYCLE_TO_DIE != 1536 || CYCLE_DELTA != 50
		|| NBR_LIVE != 21 || MAX_CHECKS != 10
		|| PROG_NAME_LENGTH % 4 != 0 || PROG_NAME_LENGTH <= 0
		|| COMMENT_LENGTH % 4 != 0 || COMMENT_LENGTH <= 0)
		return (0);
		//update return
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

static void	init_op_tab(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < REG_NUMBER + 1)
		vm->op_tab[i] = g_op_tab[i];
}

static t_vm	*t_vm_new(void)
{
	t_vm	*vm;

	!(vm = (t_vm *)malloc(sizeof(t_vm))) ? handle_error(ERR_ALLOC) : 0;
	vm->allocated = 0;
	vm->players = t_players_create(vm);	
	vm->data = t_vm_info_create(vm);
	vm->carr = t_carriages_create(vm);
	vm->mods = t_mods_create(vm);
	vm->vs = t_vs_create(vm);
	vm->cells = NULL;
	
	init_op_tab(vm);
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
