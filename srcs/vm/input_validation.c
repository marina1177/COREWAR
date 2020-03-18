#include "../../includes/vm.h"

int	is_integer(char *s)
{
	size_t	len;
	int		n;

	n = ft_atoi(s);
	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || (int)len != ft_ilen(n))
		return (0);
	if (s[0] == '-' && len == 1)
		return (0);
	return (1);
}