
#include "com.h"

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
	if (!(g_mdata = (t_mdata *)malloc(sizeof(t_mdata))))
		error_event(ERR_ALLOC);
	if (!(g_mdata->head = (t_header*)malloc(sizeof(t_header))))
		error_event(ERR_ALLOC);
	ft_memset(g_mdata->head->prog_name, '\0', PROG_NAME_LENGTH + 1);
	ft_memset(g_mdata->head->comment, '\0', COMMENT_LENGTH + 1);
	g_mdata->x = 0;
	g_mdata->y = 0;
	g_mdata->filename = NULL;
	g_mdata->name_f = 0;
	g_mdata->comm_f = 0;
	g_mdata->exec_bytes = 0;
	g_mdata->line = NULL;
}

void	compilation(void)
{
	g_mdata->exec_bytes = (g_tkn_first
			? g_tkn_last->offset + g_tkn_last->num_byte_op : 0);
	if (!(g_mbuf = (char*)malloc(sizeof(char) *
					(EXEC_START + g_mdata->exec_bytes))))
		error_event(ERR_ALLOC);
	ft_bzero(g_mbuf, EXEC_START + g_mdata->exec_bytes);
	check_dup_label();
	check_empty_file();
	translate();
	write_to_file();
}

void	read_file(char *filename)
{
	int	fd_s;

	/*if (g_flg & F_DISASM)
		disassemble();*/
	valid_filename(filename);
	if ((fd_s = open(filename, O_RDONLY, 0)) < 0)
		error_event(ERR_FOPEN);
	data_init();
	g_mdata->filename = filename;
	g_mdata->fd_s = fd_s;
	parse_file(fd_s);
	close(fd_s);
	compilation();
	free_data();
}

t_1b	put_flg(char *av)
{
	t_1b	flg;

	++av;
	flg = 0;
	while (*av)
	{
		if (*av == 'd')
			flg |= F_DISASM;
		else if (*av == 'p')
			flg |= F_OPRINT;
		else
			usage();
		++av;
	}
	return (flg);
}

void	usage(void)
{
	ft_printf("Usage: asm [-dp] [file]\n"
			"\tif no -d flag specified asm will assemble file.s\n"
			"\tuse -d for dissamble file.cor\n"
			"\twith -p flag cor-file will also be printed as a stdout.\n");
	exit(1);
}

int		main(int ac, char **av)
{
	int	i;

	if (ac == 1)
		usage();
	i = 1;
	while (i < ac)
	{
		g_flg = av[i][0] == '-' ? put_flg(av[i++]) : 0;
		if (i == ac)
			error_event(ERR_NOFILE);
		read_file(av[i]);
		++i;
	}
	return (0);
}
