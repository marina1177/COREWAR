/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:54:47 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 21:18:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

void	valid_filename(char *fname)
{
	int			i;

	i = 0;
	while (fname[i])
		i++;
	while (fname[--i])
		if (fname[i] == '.')
			break ;
	if (ft_strcmp(&fname[i], ".s"))
		error_event(ERR_FNAME);
}

void	data_init(void)
{
	g_tkn_last = NULL;
	g_tkn_first = NULL;
	g_label_first = NULL;
	g_label_last = NULL;
	if (!(g_data = (t_data *)malloc(sizeof(t_data))))
		error_event(ERR_ALLOC);
	if (!(g_data->head = (t_header*)malloc(sizeof(t_header))))
		error_event(ERR_ALLOC);
	ft_memset(g_data->head->prog_name, '\0', PROG_NAME_LENGTH + 1);
	ft_memset(g_data->head->comment, '\0', COMMENT_LENGTH + 1);
	g_data->name_f = 0;
	g_data->namelen = 0;
	g_data->comm_f = 0;
	g_data->commlen = 0;
	g_data->exec_bytes = 0;
}

void	compilation(void)
{
	g_data->exec_bytes = (g_tkn_first 
			? g_tkn_last->offset + g_tkn_last->num_byte_op : 0);
	if (!(g_buf = (char*)malloc(sizeof(char) * 
					(EXEC_START + g_data->exec_bytes))))
		error_event(ERR_ALLOC);
	ft_bzero(g_buf, EXEC_START + g_data->exec_bytes);
	check_dup_label();
	check_empty_file();
	translate();
	write_to_file();
}

void	read_file(char *filename)
{
	int	fd_s;

	valid_filename(filename);
	if ((fd_s = open(filename, O_RDONLY, 0)) < 0)
		error_event(ERR_FOPEN);
	data_init();
	g_data->filename = filename;
	g_data->fd_s = fd_s;
	parse_file(fd_s);
	close(fd_s);
	compilation();
	free_data();
}

int		main(int ac, char **av)
{
	if (ac == 2)
		read_file(av[1]);
	/*else if (ac == 3 && !ft_strcmp(av[2], "-dis"))
		read_file(av[1]);*/
	else
		error_event(ERR_NOFILE);
	return (0);
}
