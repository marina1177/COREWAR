/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:57:30 by bcharity          #+#    #+#             */
/*   Updated: 2020/07/22 22:11:04 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

char	*get_color(size_t num_byte)
{
	if (num_byte >= 4 && num_byte < 132)
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
	return (PURPUL);
}

void	ft_print_hex(unsigned char c, char *color)
{
	char *radix;

	radix = "0123456789abcdef";
	ft_putstr_fd(color, 1);
	write(1, &radix[c / 16], 1);
	write(1, &radix[c % 16], 1);
	ft_putstr_fd(EOC, 1);
}

void	ft_print_char(unsigned char c, char *color)
{
	ft_putstr_fd(color, 1);
	if (c >= ' ' && c <= '~')
		write(1, &c, 1);
	else
		write(1, ".", 1);
	ft_putstr_fd(EOC, 1);
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

void	print_bits(size_t size, void *ptr, char space)
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
