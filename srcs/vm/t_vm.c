/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/07/04 23:26:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	is_valid_op_h(void)
{	
	IND_SIZE != STD_IND_SIZE ? error_op_h("IND_SIZE", STD_IND_SIZE) : 0;
	REG_SIZE != STD_REG_SIZE ? error_op_h("REG_SIZE", STD_REG_SIZE) : 0;
	DIR_SIZE != STD_DIR_SIZE ? error_op_h("DIR_SIZE", STD_DIR_SIZE) : 0;
	REG_CODE != STD_REG_CODE ? error_op_h("REG_CODE", STD_REG_CODE) : 0;
	DIR_CODE != STD_DIR_CODE ? error_op_h("DIR_CODE", STD_DIR_CODE) : 0;
	IND_CODE != STD_IND_CODE ? error_op_h("IND_CODE", STD_IND_CODE) : 0;
	MAX_ARGS_NUMBER != STD_MAX_ARGS_NUMBER ? error_op_h(
		"MAX_ARGS_NUMBER", STD_MAX_ARGS_NUMBER) : 0;
	MAX_PLAYERS > STD_MAX_PLAYERS || MAX_PLAYERS < 1 ? error_range_op_h(
		"MAX_PLAYERS", 1, STD_MAX_PLAYERS) : 0;	 
	MEM_SIZE < STD_MEM_SIZE_MIN || MEM_SIZE > STD_MEM_SIZE_MAX ? \
	error_range_op_h("MEM_SIZE", STD_MEM_SIZE_MIN, STD_MEM_SIZE_MAX) : 0;	  
	IDX_MOD != MEM_SIZE / 8  ? error_op_h("IDX_MOD", MEM_SIZE / 8) : 0;
	CHAMP_MAX_SIZE != MEM_SIZE / 6 ? error_op_h(
		"CHAMP_MAX_SIZE", MEM_SIZE / 6) : 0;
	REG_NUMBER != STD_REG_NUMBER ? error_op_h(
		"REG_NUMBER", STD_REG_NUMBER) : 0;
	CYCLE_TO_DIE < 1 || CYCLE_TO_DIE > 3072 ? error_range_op_h(
		"CYCLE_TO_DIE", 1, 3072) : 0;
	CYCLE_DELTA != STD_CYCLE_DELTA ? error_op_h(
		"CYCLE_DELTA", STD_CYCLE_DELTA) : 0;
	NBR_LIVE != STD_NBR_LIVE ? error_op_h("NBR_LIVE", STD_NBR_LIVE) : 0;
	MAX_CHECKS != STD_MAX_CHECKS ? error_op_h("MAX_CHECKS", STD_MAX_CHECKS) : 0;
	PROG_NAME_LENGTH != STD_PROG_NAME_LENGTH ? error_op_h(
		"PROG_NAME_LENGTH", STD_PROG_NAME_LENGTH) : 0;
	COMMENT_LENGTH != STD_COMMENT_LENGTH ? error_op_h(
		"PROG_NAME_LENGTH", STD_COMMENT_LENGTH) : 0;
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
