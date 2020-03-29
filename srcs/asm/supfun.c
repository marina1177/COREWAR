#include "../../includes/com.h"

void    bits_to_str(size_t size, void *ptr, char space)
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
	while ((str[i]) == ' ' || (str[i]) == '	')
		i++;
	if (str[i] == '-')
		neg = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += ((int)str[i] - 48);
		printf("num = %lld\n",num);
		i++;
	}
	num = (neg == 1 ? -num : num);
	printf("%s_atoi_%lld\n", str,num);
	size == 1 ? (num = (u_int8_t)num) : 1;
	size == 2 ? (num = (int16_t)num) : 1;
	size == 4 ? (num = (int32_t)num) : 1;
	printf("ret_atoi_%lld\n", num);
	return (num);
}

int		is_lblchar(char c)
{
	char	*ptr;

	ptr = LABEL_CHARS;
	while(*ptr != '\0')
	{
		if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

char *skip_space(char *s)
{
	while(s[g_data->x] == ' ' || s[g_data->x] == '	')
		g_data->x++;
	return(&(s[g_data->x]));
}

char *skip_comment(char *s)
{
	char	*pnt;
	int		len;
	//char	end_ch;

	pnt = ft_strstr(s, "#");
	if (pnt != NULL)
		*pnt = '\0';
	pnt = ft_strstr(s, ";");
	if (pnt != NULL)
		*pnt = '\0';
	len = ft_strlen(s);
	while(!IS_BLANK(s[len--]));
	return(s);
}
