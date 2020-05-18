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

static void		init_vschange(t_vs	*vs)
{
	vs->change_begin_len += ft_strlen(A_CYCLE);
	vs->change_begin_len += ft_strlen(A_STATE_REF);
	vs->change_begin_len += ft_strlen(M_STATE) + ft_strlen(A_ERR_CODE)
		+ ft_strlen(A_TOTAL_PROC) + ft_strlen(A_CYCLE_TO_DIE)
		+ ft_strlen(A_NBR_LIVE);
	vs->change_begin_len += ft_strlen(A_PLAYERS_REF);
	vs->change_begin_len += ft_strlen(M_PLAYERS) + ft_strlen(A_IS_ALIVE)
		+ ft_strlen(A_ID) + ft_strlen(A_LAST_LIVE) + ft_strlen(A_LPP);
	vs->change_begin_len += ft_strlen(A_CAR_REF);
	vs->change_begin_len += ft_strlen(M_CARRIAGE) + ft_strlen(A_ID)
		+ ft_strlen(A_OP_CODE) + ft_strlen(A_PLACE);
	vs->change_begin_len += ft_strlen(M_CELLS) + ft_strlen(A_CELL_ADDR)
		+ ft_strlen(A_PLAYER_ID);
}

static void		init_vsconst(t_vs	*vs)
{
	vs->const_begin_len += ft_strlen(M_CONST) + ft_strlen(A_END_1);
	vs->const_begin_len += ft_strlen(A_MEMSIZE);
	vs->const_begin_len += ft_strlen(A_CYCLEDELTA);
	vs->const_begin_len += ft_strlen(A_PLAYERS_NUM);
	vs->const_begin_len += ft_strlen(A_MAXCHECKS);
	vs->const_begin_len += ft_strlen(A_C_NBR_LIVE);
	vs->const_begin_len += ft_strlen(A_C_CYCLE_TO_DIE);
}

static void		init_refresh(t_vs	*vs)
{
	vs->state_refresh = 1;
	vs->players_refresh = 1;
	vs->carriages_refresh = 1;
	vs->cells_refresh = 1;
	vs->const_begin_len = 0;
	vs->change_begin_len = 0;
}

static t_vs	*t_vs_new(void)
{
	t_vs	*vs;
	int		i;

	if ((vs = (t_vs *)malloc(sizeof(t_vs))))
	{
		i = 0;
		init_refresh(vs);
		init_vsconst(vs);
		init_vschange(vs);
		vs->error_code = 0;
	}
	else
	{
		handle_error(ERR_ALLOC);
	}
	return (vs);
}

t_vs		*t_vs_create(t_vm *vm)
{
	t_vs	*new;

	new = NULL;
	if (!vm->vs)
	{
		new = t_vs_new();
	}
	return (vm->vs ? vm->vs : new);
}
