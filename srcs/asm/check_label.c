/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:55:39 by bcharity          #+#    #+#             */
/*   Updated: 2020/07/22 21:57:27 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

void			check_empty_file(void)
{
	if ((g_tkn_first == NULL && g_label_first == NULL)
	|| (g_tkn_first == NULL && !g_label_first->new_line))
	{
		g_mdata->x = 0;
		g_mdata->y += 1;
		put_error("Syntax error at token:", 1);
	}
	else if ((g_tkn_last && g_tkn_last->new_line == 0))
	{
		error_event(FOGOT_NL);
	}
	else if (g_label_last != NULL && g_label_last->new_line)
		return ;
}

void			del_dubl(t_lbl_lst *ptr2)
{
	t_lbl_lst	*tmp;

	tmp = ptr2->next;
	ptr2->next = tmp->next;
	free(tmp->label);
	free(tmp);
}

void			check_dup_label(void)
{
	t_lbl_lst	*ptr1;
	t_lbl_lst	*ptr2;

	ptr1 = g_label_first;
	while (ptr1 != NULL && ptr1->next != NULL)
	{
		ptr2 = ptr1;
		while (ptr2->next != NULL)
		{
			if (!ft_strcmp(ptr1->label, ptr2->next->label))
			{
				del_dubl(ptr2);
				ptr2->next ? ptr2 = ptr2->next : NULL;
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

static size_t	label_size(char *s)
{
	int	tmp;

	tmp = g_mdata->x;
	while (s[tmp] && s[tmp] != LABEL_CHAR
	&& s[tmp] != DIRECT_CHAR && !IS_BLANK(s[tmp]))
		++tmp;
	if (s[tmp] == LABEL_CHAR)
		return (tmp - g_mdata->x);
	return (0);
}

void			check_label(char *line)
{
	size_t		size;

	if ((size = label_size(line)))
	{
		add_lbl(&(line[g_mdata->x]), size);
		if (g_mdata->exist_nl != 0)
		{
			g_label_last->new_line = 1;
		}
		else
		{
			g_mdata->x += size + 2;
			put_error("Syntax error at token:", 1);
		}
		g_mdata->x += size + 1;
	}
}
