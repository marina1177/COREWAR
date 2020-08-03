/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dasm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arz <arz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/08/03 23:03:19 by arz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

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

int		errors_event(int x, int fd)
{
	if (fd > 0)
		close(fd);
	if (x == 1)
		ft_printf("Invalid file\n");
	else if (x == 2)
		ft_printf("Invalid champion code\n");
	else
		ft_printf("Error writing the file\n");
	return (0);
}

int 	disasm(char *file_name, t_dasm *as)
{
	if ((as->fd = open_file(file_name)) > 0 && verification_magic_header(as->fd))
	{
		if (!(read_champion_name(as, as->fd)))
			return (errors_event(1, as->fd));
		if (skip_null(as->fd) == 0)
			return (errors_event(1, as->fd));
		if (!(champion_code_size(as, as->fd)))
			return (errors_event(1, as->fd));
		if (!(read_champion_comment(as, as->fd)))
			return (errors_event(1, as->fd));
		if (skip_null(as->fd) == 0)
			return (errors_event(1, as->fd));
		if (!(read_champ_code(as)))
			return (errors_event(2, as->fd));
		if (!(write_2_file(as, file_name)))
			return (errors_event(0, as->fd));
		return (1);
	}
	else
		return (errors_event(1, 0));
}

void	free_dasm(t_dasm *as)
{
	if (as)
	{
		free(as->champ_code);
		free(as->comment);
		free(as->name);
		free(as);
	}
}

int		main_dasm(char *name_file)
{
	t_dasm	*as;

	if (name_file && (as = malloc_dasm()))
	{
		if (!(disasm(name_file, as)))
		{
			free_dasm(as);
			return (0);
		}
		free_dasm(as);
		return (1);
	}
	return (0);
}
