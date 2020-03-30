#include "../../includes/com.h"

static char			*new_filename(char *filename)
{
	u_int16_t		len;
	char			*new_name;
	u_int16_t		i;

	len = -1;
	while (filename[++len] + 1)
		if (filename[len] == '.'
		&& filename[len + 1] == 's'
		&& filename[len + 2] == '\0')
			break ;
	if (!(new_name = (char*)malloc((len + 5) + 1)))
		error_event(ERR_ALLOC);
	i = -1;
	while (++i < len)
		new_name[i] = filename[i];
	ft_strcpy(&(new_name[i]), ".cor");
	return (new_name);
}

void				write_to_file()
{
	int				fd;
	char			*new_name;

	new_name = new_filename(g_data->filename);
	if ((fd = open(new_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		error_event(ERR_CRFHEX);
	//ft_printf("%sWriting output program to %s%s\n", GREEN, new_name, EOC);
	ft_putstr("Writing output program to ");
	ft_putstr(new_name);
	write(1,"\n",1);

	free(new_name);
	if (write(fd, g_buf, EXEC_START + g_data->exec_bytes) == -1)
	{
		free(g_buf);
		close(fd);
		error_event(ERR_WRFHEX);
	}
	free(g_buf);
	close(fd);
}
