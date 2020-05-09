#include "../../includes/vm.h"

void				print_byte(unsigned char c)
{
	unsigned char	test;
	int				i;

	i = 0;
	test = 0b10000000;

	while (i < 8)
	{
		if (c & test)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		test = test >> 1;
		i++;
	}
	write(1, "\n", 1);
}

static void			ft_print_hex(unsigned char c)
{
	char			*radix;

	radix = "0123456789abcdef";
	write(1, &radix[c / 16], 1);
	write(1, &radix[c % 16], 1);
}

static void			ft_print_char(unsigned char c)
{
	if (c >= ' ' && c <= '~')
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

void				print_memory(const void *addr, size_t size)
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
			ft_print_hex(ptr[i + j]);
			if (j++ % 2)
				write(1, " ", 1);
		}
		while (j < 16)
		{
			write(1, "  ", 2);
			if (j++ % 2)
				write(1, " ", 1);
		}
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_print_char(ptr[i + j]);
			j++;
		}
		write(1, "\n", 1);
		i += 16;
	}
}
