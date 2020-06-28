/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 15:54:27 by bcharity          #+#    #+#             */
/*   Updated: 2020/06/28 15:54:57 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/com.h"

void		print_filename(void)
{
	if (!g_mdata->filename)
		return ;
	ft_putendl_fd("", 2);
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd(g_mdata->filename, 2);
	ft_putstr_fd(EOC, 2);
	write(2, ":\n", 2);
}

void		print_error_info(int x, int y)
{
	if (!g_mdata || x == -1 || y == -1)
		return ;
	print_filename();
	ft_putstr_fd(YELLOW, 2);
	write(2, "Ln ", 3);
	ft_putnbr_fd(y, 2);
	write(2, ", Col ", 6);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(EOC, 2);
	write(2, ": ", 2);
}
