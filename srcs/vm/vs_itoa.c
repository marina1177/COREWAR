#include "../../includes/vm.h"

static int			count(int n)
{
	int	num;

	num = 0;
	if (n < 0)
	{
		num++;
		n = -n;
	}
	if (n == 0)
		num = 1;
	while (n != 0)
	{
		num++;
		n /= 10;
	}
	return (num);
}

static char			*to_str(int n, int num, short ui, char *s)
{
	int		i;
//	char	*s;

	i = 0;
//	s = ft_strnew((num) * sizeof(char));
	if (s)
	{
		while (i < num)
		{
			s[num - i - 1] = n % 10 + 48;
			n = n / 10;
			i++;
		}
		if (s[0] == '0' && s[1])
			s[0] = '-';
		if (ui)
			s[1] = '2';
	}
	return (s);
}

int					vs_itoa(int n, char *s)
{
	int				num;
	short			ui;

	ui = 0;
	num = count(n);
	if (n < 0)
	{
		n = -n;
	}
	if (n == -2147483648)
	{
		n = 147483648;
		ui = 1;
	}
	to_str(n, num, ui, s);
	return (num);
}