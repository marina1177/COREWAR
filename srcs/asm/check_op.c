/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:11:15 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 20:37:25 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

int		search_op(char *line)
{
	static const char	*types[17] = {NULL, "live", "ld", "st", "add", "sub",
									"and", "or", "xor", "zjmp", "ldi", "sti",
									"fork", "lld", "lldi", "lfork", "aff"};
	size_t				size;
	int					i;

	i = 17;
	while (--i)
	{
		size = ft_strlen(types[i]);
		if (ft_strnequ(&(line[g_data->x]), types[i], size))
			break ;
	}
	if (i == 0)
		put_error("Lexical error: invalid instruction", 1);
	g_data->x += size;
	return (i - 1);
}

t_token	*new_token(void)
{
	t_token		*new;

	new = NULL;
	if (!(new = (t_token*)malloc(sizeof(t_token))))
		error_event(ERR_ALLOC);
	new->next = NULL;
	new->prev = NULL;
	if (g_tkn_last == NULL && g_tkn_first == NULL)
	{
		g_tkn_first = new;
		g_tkn_last = g_tkn_first;
		new->offset = 0;
		new->num_byte_op = 0;
	}
	else
	{
		g_tkn_last->next = new;
		new->prev = g_tkn_last;
		new->num_byte_op = 0;
		new->offset = g_tkn_last->offset
			+ g_tkn_last->num_byte_op;
	}
	g_data->exec_bytes += g_tkn_last->num_byte_op;
	g_tkn_last = new;
	return (new);
}

void	add_token(int indx_op)
{
	t_token		*new;

	new = NULL;
	new = new_token();
	new->op = &(g_op_tab[indx_op]);
	new->new_line = 0;
	new->y = g_data->y;
	new->x = g_data->x;
}

void	check_op(char *line)
{
	if (!(&(line[g_data->x])) || line[g_data->x] == '\0')
		return ;
	skip_space(line);
	add_token(search_op(line));
	g_tkn_last->num_byte_op = 1;
	if (g_tkn_last->op->args_types_code)
	{
		g_tkn_last->num_byte_op += 1;
	}
	skip_space(line);
	parse_args(line);
}
