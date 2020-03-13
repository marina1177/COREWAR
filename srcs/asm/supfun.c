#include "../../includes/com.h"

void    print_bits(size_t size, void *ptr, char space)
{
    unsigned char    *b;
    unsigned char    byte;
    int                i;
    int                j;

    b = (unsigned char*)ptr;
    i = size - 1;
    j = 7;
    while (i >= 0)
    {
        while (j >= 0)
        {
            byte = (b[i] >> j) & 1;
            ft_putchar(byte + '0');
            j--;
        }
        if (space == 1)
            ft_putchar(' ');
        j = 7;
        i--;
    }
    ft_putchar('\n');
}

int32_t		ft_atoi_cor(const char *str, u_int8_t size)
{
	int				neg;
	int				i;
	int64_t			num;

	i = 0;
	neg = 0;
	num = 0;
	while ((str[i]))
		i++;
	if (str[i] == '-')
		neg = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += ((int)str[i] - 48);
		i++;
	}
	num = (neg == 1 ? -num : num);
	size == 1 ? (num = (u_int8_t)num) : 1;
	size == 2 ? (num = (int16_t)num) : 1;
	size == 4 ? (num = (int32_t)num) : 1;
	return (num);
}

char *skip_space(char *s)
{
	while(*s == ' ' || *s == '	')
		s++;
	return(s);
}

char *skip_comment(char *s)
{
	char	*pnt;

	pnt = ft_strstr(s, "#");
	if (pnt != NULL)
		*pnt = '\0';
	pnt = ft_strstr(s, ";");
	if (pnt != NULL)
		*pnt = '\0';
	return(s);
}
