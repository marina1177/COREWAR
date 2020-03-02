#include "com.h"

int		valid_filename(char *filename)
{
	char	*ext;

	printf("filename = %s\n", filename);
	ext = ft_memchr(filename, '.', ft_strlen(filename));
	if(ft_strcmp(ext + 1, "s"))
		return (0);
	return (1);
}

int	parse_file(int fd_s)
{
	char	*buf;

	//ft_memset(g_name, '\0', 128);
	//ft_memset(g_comment, '\0', 2048);

	g_snum = 0;
	while(get_next_line(fd_s, &buf) > 0)//!!!!СОХРАНЯТЬ NEWLINE!!!!
	{
		printf("get_%s\n", buf);
		parse_str(&buf); //get token
		g_snum++;
		//free(buf);
	}
	free(buf);
	return(1);

}

int		data_malloc()
{
	g_tkn_first = g_tkn_last;
	g_label_first = g_label_last;
	g_data = (t_data *)malloc(sizeof(t_data));
	if(!g_data)
	{
		printf("g_data malloc error\n");
		return (0);
	}
	g_data->head = (t_header*)malloc(sizeof(t_header));
	//g_data->head->prog_name[129] = '\0';
        ft_memset(g_data->head->prog_name, '\0', PROG_NAME_LENGTH+1);
	ft_memset(g_data->head->comment, '\0', COMMENT_LENGTH + 1);
	g_data->name_f = 0;
	g_data->namelen = 0;
	g_data->comm_f = 0;
	g_data->commlen = 0;
	g_data->tkn_lst = g_tkn_first;
	//g_data->head = g_head;

	return (1);
}

void	read_file(char *filename)
{
	int	fd_s;

	if (!valid_filename(filename))
	{
		printf("validfile error\n");
		error();
	}

	if ((fd_s = open(filename, O_RDONLY, 0)) < 0)
	{
		printf("fd error\n");
		error();
	}
	if (!data_malloc())
		error();
	//printf("g_data->head->prog_name =%s\n", g_data->head->prog_name);

	g_data->fd_s = fd_s;
	if(!parse_file(fd_s))//!!!!!!!!!!!!!!обработать errmsg нормально
	{
		printf("parse_file error\n");
		error();
	}
	close(fd_s);
}

int		main(int ac, char **av)
{
	if (ac < 2)
		printf("error - where arguments?\n");

	printf("-------main-----%s_\n", (g_op_tab[1]).name);

	read_file(av[ac - 1]);//считываю файл по-строчно и заполняю g_data & g_lbl

}
