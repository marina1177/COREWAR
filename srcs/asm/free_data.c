/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 02:16:26 by bcharity          #+#    #+#             */
/*   Updated: 2020/07/22 22:06:17 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	freesplit(t_token *tmp)
{
	int	i;

	i = 0;
	while (i < (tmp)->op->args_num)
	{
		if ((tmp)->cnt_args < (tmp)->op->args_num
			&& i == tmp->cnt_args)
		{
			break ;
		}
		free(tmp->args[i]->arg);
		free(tmp->args[i]);
		++i;
	}
}

void	free_token(void)
{
	t_token	*tmp;

	if (!g_tkn_first)
		return ;
	while (g_tkn_first != NULL)
	{
		tmp = g_tkn_first;
		g_tkn_first = (g_tkn_first)->next;
		freesplit(tmp);
		free(tmp);
	}
}

void	free_label(void)
{
	t_lbl_lst	*temp;

	if (g_label_first == NULL)
		return ;
	while (g_label_first != NULL)
	{
		temp = g_label_first;
		free(temp->label);
		g_label_first = g_label_first->next;
		free(temp);
	}
}

void	free_data(void)
{
	if (g_mbuf != NULL)
		free(g_mbuf);
	if (g_mdata)
	{
		if (g_mdata->fd_s)
		{
			get_line(-1, NULL);
			close(g_mdata->fd_s);
		}
		if (g_mdata->line != NULL)
		{
			free(g_mdata->line);
		}
		free(g_mdata->head);
		free(g_mdata);
	}
	if (g_tkn_first)
		free_token();
	if (g_label_first)
		free_label();
	exit(0);
}
