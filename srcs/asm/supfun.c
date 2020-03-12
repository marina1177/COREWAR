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
