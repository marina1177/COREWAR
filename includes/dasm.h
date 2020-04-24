/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:07:24 by cdemetra          #+#    #+#             */
/*   Updated: 2020/04/13 11:37:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include <unistd.h>
//# include "op.h"
//# include "vm.h"
# include "./libft/includes/libft.h"
# include 	"./libft/includes/ft_printf.h"
# include "com.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>


# include <fcntl.h>

# define _SPACE_ " "
# define _DOT_COR_ ".s"
# define MASK2 0xFFFF;
# define MASK4 0xFFFFFFFF;


typedef struct	s_dasm
{
	int 		fd;
	char		*name;
	char		*comment;
	int			champ_code_size;
	int         ccs;
	char		*champ_code;
}				t_dasm;

/*
** open_create.c
*/

int		open_file(char *name);
int		create_file(char *name);

/*
** read_byte_code.c
*/

int 	read_argument_without_types(t_dasm *ds, int opr);
int 	read_operation_argument(int opr, t_dasm *ds);
int		read_champ_code(t_dasm *ds);

/*
** read_name_comment.c
*/

int		read_byte(char *byte, int size, int fd);
int		read_champion_comment(t_dasm *as, int fd);
int		read_champion_name(t_dasm *as, int fd);
int		champion_code_size(t_dasm *as, int fd);

/*
** validation_dasm.c
*/

int		verification_magic_header(int fd);
int		skip_null(int fd);


/*
** write_code_1.c
*/

int		write_tdir2(t_dasm *ds, int value);
int 	write_tdir(t_dasm *ds, int opr);
int		write_treg(t_dasm *ds);
int 	write_tind(t_dasm *ds);
int		write_arg(t_dasm *ds, int opr, char type);

/*
** write_code_2.c
*/

char 	*write_code(t_dasm *ds, char *str);
int		 neg_numb_conversion(unsigned int value, int byte);

/*
** write_to_file.c
*/

int 	write_to_file(t_dasm *ds, char *name);
#endif
