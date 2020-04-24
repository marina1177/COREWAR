/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/04/07 14:28:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/includes/ft_printf.h>
#include "dasm.h"

t_dasm	*malloc_dasm(void)
{
	t_dasm	*dasm;

	dasm = NULL;
	if ((dasm = (t_dasm*)malloc(sizeof(t_dasm))))
	{
		dasm->comment = NULL;
		dasm->name = NULL;
		dasm->champ_code = NULL;
		dasm->fd = 0;
		dasm->ccs = 0;
		dasm->champ_code_size = 0;
	}
	return (dasm);
}

int 	disasm(char *file_name, t_dasm *as)
{
	if ((as->fd = open_file(file_name)) > 0 && verification_magic_header(as->fd))
	{
		if (!(read_champion_name(as, as->fd)))
			return (0);
		if (skip_null(as->fd) == 0)
			return (0);
		if (!(champion_code_size(as, as->fd)))
			return (0);
		if (!(read_champion_comment(as, as->fd)))
			return (0);
		if (skip_null(as->fd) == 0)
			return (0);
		if (!(read_champ_code(as)))
			return (0);
		if (!(write_to_file(as, file_name)))
			return (0);
		return (1);
		printf("champ code %s\n size_code = %d\n counter = %d\n", as->champ_code, as->champ_code_size, as->ccs);
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		i;
	t_dasm	*as;

	i = 1;
	if (ac > 1 && (as = malloc_dasm()))
	{
		while (i < ac)
		{
			if (!(disasm(av[i], as)))
				printf("Error\n");
			i++;
		}
	}
	return (0);
}
