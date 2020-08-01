/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_op_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 12:53:22 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 13:00:53 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	is_valid_consts(void)
{
	MAX_ARGS_NUMBER != STD_MAX_ARGS_NUMBER ? error_op_h(
		"MAX_ARGS_NUMBER", STD_MAX_ARGS_NUMBER) : 0;
	MAX_PLAYERS > STD_MAX_PLAYERS || MAX_PLAYERS < 1 ? error_range_op_h(
		"MAX_PLAYERS", 1, STD_MAX_PLAYERS) : 0;
	MEM_SIZE < STD_MEM_SIZE_MIN || MEM_SIZE > STD_MEM_SIZE_MAX ? \
	error_range_op_h("MEM_SIZE", STD_MEM_SIZE_MIN, STD_MEM_SIZE_MAX) : 0;
	IDX_MOD != MEM_SIZE / 8 ? error_op_h("IDX_MOD", MEM_SIZE / 8) : 0;
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
}

static void	is_valid_ind_reg_dir(void)
{
	IND_SIZE != STD_IND_SIZE ? error_op_h("IND_SIZE", STD_IND_SIZE) : 0;
	REG_SIZE != STD_REG_SIZE ? error_op_h("REG_SIZE", STD_REG_SIZE) : 0;
	DIR_SIZE != STD_DIR_SIZE ? error_op_h("DIR_SIZE", STD_DIR_SIZE) : 0;
	REG_CODE != STD_REG_CODE ? error_op_h("REG_CODE", STD_REG_CODE) : 0;
	DIR_CODE != STD_DIR_CODE ? error_op_h("DIR_CODE", STD_DIR_CODE) : 0;
	IND_CODE != STD_IND_CODE ? error_op_h("IND_CODE", STD_IND_CODE) : 0;
}

int			is_valid_op_h(void)
{
	is_valid_ind_reg_dir();
	is_valid_consts();
	return (1);
}
