#include "../../includes/com.h"

void		put_error(char *err, int type)
{
	if (type)
	{
		printf("%s [%d:%d]\n", err, g_data->y, g_data->x);
		errno = EINVAL;
	}
	else
   		printf("%s\n", err);
	exit(errno);
}

void		print_error(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit(1);
}

void	error_line(char *event, char *line, int x)
{
	//print_error_info(x, g_snum);
//	print_line_error(event, line, x);
	printf("event_%s_x_%d\n", event, x);
	ft_strdel(&line);
	free_data();
	exit(1);
}

void	error_event(char *event)
{
	//ft_putstr_fd(RED, 2);
	print_error(event);
	free_data();
}

void		error(void)
{
	char *s;

	s = "Error\n";
	write(2, s, ft_strlen(s));
	exit(0);
}

//**************************************

/*void		print_line_error(char *message, char *line, int x)
{
	description_token(message, g_data->token);
	write(2, line, x);
	ft_putstr_fd(RED, 2);
	write(2, line + x, g_data->x - x + 1);
	ft_putstr_fd(EOC, 2);
	ft_putendl_fd(line + g_data->x + 1, 2);
}*/

void		print_filename(void)
{
	if (!g_data->filename)
		return ;
	ft_putendl_fd("", 2);
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd(g_data->filename, 2);
	ft_putstr_fd(EOC, 2);
	write(2, ":\n", 2);
}

void		print_error_info(int x, int y)
{
	if (!g_data || x == -1 || y == -1)
		return ;
	print_filename();
	ft_putstr_fd(YELLOW, 2);
	write(2, "Ln ", 3);
	ft_putnbr_fd(y, 2);
	write(2, ", Col ", 6);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(EOC, 2);
	write(2, ": ", 2);
}

