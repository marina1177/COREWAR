/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:18:21 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 15:40:37 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

static	void	add_tail_list(t_lbl_lst **new)
{
	if (g_label_first == NULL && g_label_last == NULL)
	{
		g_label_first = *new;
		g_label_last = g_label_first;
	}
	else
		g_label_last->next = *new;
	(*new)->offset = g_tkn_last->offset + g_tkn_last->num_byte_op;
}

static void		add_top_list(t_lbl_lst **new)
{
	if (g_label_first == NULL)
	{
		g_label_first = *new;
		g_label_last = g_label_first;
		(*new)->offset = 0;
	}
	else if (g_label_first)
	{
		g_label_last->next = *new;
		(*new)->offset = g_label_last->offset;
	}
}

void			add_lbl(char *s, size_t size)
{
	t_lbl_lst	*new;

	if (!(new = (t_lbl_lst *)malloc(sizeof(t_lbl_lst))))
		error_event(ERR_ALLOC);
	new->next = NULL;
	if (g_tkn_first == NULL)
		add_top_list(&new);
	else
		add_tail_list(&new);
	g_label_last = new;
	g_label_last->label = ft_strsub(s, 0, size);
	g_label_last->new_line = 0;
}
