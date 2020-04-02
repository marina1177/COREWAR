
#include "com.h"

void	int_to_hex(int32_t dec, int dir_size, u_int32_t *place)
{
	int			move;
	int			buf;
	u_int8_t	tmp;

	buf = dir_size;
	move = 0;
	while (dir_size)
	{
		tmp = (u_int8_t)((dec >> move) & 0xFF);
		g_buf[*place + dir_size - 1] = tmp;
		move += 8;
		dir_size--;
	}
	*place += buf;
}

int		ft_findchar(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i + 1);
		i++;
	}
	if (str[i] == (char)c)
		return (i + 1);
	return (0);
}

int		ft_strmerge(char **dest, char **srcs)
{
	char				*ret;
	char				*fresh;
	char				*dst;
	char				*src;

	ret = 0;
	dst = *dest;
	src = *srcs;
	if (dst && src && (fresh = ft_strnew(ft_strlen(dst) + ft_strlen(src))))
	{
		ret = fresh;
		while (*dst)
			*fresh++ = (char)*dst++;
		while (*src)
			*fresh++ = (char)*src++;
	}
	else
		return (0);
	ft_strdel(dest);
	ft_strdel(srcs);
	*dest = ret;
	*srcs = src;
	return (1);
}
