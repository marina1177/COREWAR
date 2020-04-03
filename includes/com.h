/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:41:56 by bcharity          #+#    #+#             */
/*   Updated: 2020/04/01 17:41:56 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COM_H
# define COM_H

# define TRUE 1
# define FALSE 0

# include "../libft_clala/includes/libft.h"
# include "../libft_clala/includes/ft_printf.h"

//# include "../libft/includes/libft.h"

# include "op.h"
# include "asm.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <stdio.h>

/*
** We can use:
** open read lseek write close malloc
** realloc free perror strerror exit
*/

# define EOC	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define WHITE	"\033[1;37m"
# define BLACK	"\033[0;30m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define PURPUL	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define GRAY	"\033[1;30m"

#endif
