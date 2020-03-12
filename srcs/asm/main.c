#include "../../includes/com.h"

void	valid_filename(char *filename)
{
	char	*ext;

	printf("filename = %s\n", filename);
	ext = ft_memchr(filename, '.', ft_strlen(filename));
	if (ft_strcmp(ext + 1, "s"))
		error_event(ERR_FNAME);
}

void	parse_file(int fd_s)
{
	char	*buf;
	int		size;

	g_snum = 0;
	while ((size = get_next_line(fd_s, &buf)) > 0)//!!!!СОХРАНЯТЬ NEWLINE!!!!
	{
		printf("get_%s\n", buf);
		parse_str(&buf);
		g_snum++;
		printf("NUM_STR = %ld\n", g_snum);
		ft_strdel(&buf);
	}
	if (size == -1)
		error_event(ERR_READING);

	//validation();

}

void	data_init()
{
	g_tkn_last = NULL;
	g_tkn_first = NULL;

	g_label_first = NULL;
	g_label_last = NULL;

	if (!(g_data = (t_data *)malloc(sizeof(t_data))))
		error_event(ERR_ALLOC);
	if (!(g_data->head = (t_header*)malloc(sizeof(t_header))))
		error_event(ERR_ALLOC);
	ft_memset(g_data->head->prog_name, '\0', PROG_NAME_LENGTH+1);
	ft_memset(g_data->head->comment, '\0', COMMENT_LENGTH + 1);
	g_data->name_f = 0;
	g_data->namelen = 0;
	g_data->comm_f = 0;
	g_data->commlen = 0;
}

void		compilation(void)
{
	if (!(g_buf = (char*)malloc(sizeof(char) * (EXEC_START + g_data->exec_bytes))))
		error_event(ERR_ALLOC);
	ft_bzero(g_buf, EXEC_START + g_data->exec_bytes);
	translate();
	//write_to_file();
}


void	read_file(char *filename, int flag)
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
	printf("add bonus flag = %d\n", flag);
}

int		main(int ac, char **av)
{
//	printf("-------main-----%s_\n", (g_op_tab[1]).name);

	if (ac == 2)
		read_file(av[1], 0);
	else if (ac == 3 && !ft_strcmp(av[2], "-test"))
		read_file(av[1], 1);
	else
		error_event(ERR_NOFILE);
	return (0);
}
