#include "../../includes/com.h"

static char	*get_color(size_t num_byte)
{

	if(num_byte >= 0 && num_byte < 4)
		return (PURPUL);
	else if (num_byte >= 4 && num_byte < 132)
		return (C_YEL);
	else if ((num_byte >= 132 && num_byte < 136)
		|| (num_byte >= 2188 && num_byte < 2192))
		return (GRAY);
	else if (num_byte >= 136 && num_byte < 140)
		return (CYAN);
	else if (num_byte >= 140 && num_byte < 2188)
		return (C_RED);
	else if (num_byte >= 2192)
		return (CYAN);
	return(WHITE);
}

static void	ft_print_hex(unsigned char c, char *color)
{
	char *radix;

	radix = "0123456789abcdef";
	ft_putstr_fd(color, 1);

	write(1, &radix[c / 16], 1);
	write(1, &radix[c % 16], 1);

	ft_putstr_fd(EOC, 1);
}

static void	ft_print_char(unsigned char c, char *color)
{
	ft_putstr_fd(color, 1);
	if (c >= ' ' && c <= '~')
		write(1, &c, 1);
	else
		write(1, ".", 1);
	ft_putstr_fd(EOC, 1);
}

void		print_memory(const void *addr, size_t size)
{
	size_t i;
	size_t j;
	unsigned char *ptr;

	i = 0;
	j = 0;
	ptr = (unsigned char*)addr;
	while (i < size)
	{
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_print_hex(ptr[i + j], get_color(i + j));
			if (j % 2)
				write(1, " ", 1);
			j++;
		}
		while (j < 16)
		{
			write(1, "  ", 2);
			if (j % 2)
				write(1, " ", 1);
			j++;
		}
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_print_char(ptr[i + j], get_color(i + j));
			j++;
		}
		write(1, "\n", 1);
		i += 16;
	}
}

void	bits_to_str(size_t size, void *ptr, char space)
{
	unsigned char	*b;
	unsigned char	byte;
	int				i;
	int				j;

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


void		print_bits(size_t size, void *ptr, char space)
{
	unsigned char	*b;
	unsigned char	byte;
	int				i;
	int				j;
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
