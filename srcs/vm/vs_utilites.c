#include "../../includes/vm.h"

int		count_dig(size_t val)
{
	int		i;
	size_t	n;

	i = 0;
	n = val;
	//if (n < 0)
	//	i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		vs_putstr_fd(int fd, const char *s)
{
	size_t i;

	if (!s || !*s)
		return (0);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}

int		vs_strcpy(char *dest, const char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = dest;
	while (*src)
	{
		*(temp++) = *(src++);
		i++;
	}
	*temp = '\0';
	return (i);
}


