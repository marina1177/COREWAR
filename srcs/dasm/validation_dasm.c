/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_dasm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:30:25 by cdemetra          #+#    #+#             */
/*   Updated: 2020/04/07 14:20:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int		verification_magic_header(int fd)
{
	unsigned int		m_header;
	char				*lk;

	lk = (char*)&m_header;

	if (read_byte(lk, 4, fd) && m_header == COREWAR_EXEC_MAGIC)
		return (1);
	else
		return (0);
}

int		skip_null(int fd)
{
	int		a;
	int		x;

	x = read(fd, &a, 4);
	if (x == 4 && a == 0x0)
		return (1);
	return (0);
}
