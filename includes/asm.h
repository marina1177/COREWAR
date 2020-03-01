/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 23:10:00 by bcharity          #+#    #+#             */
/*   Updated: 2020/02/27 23:10:01 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef ASM_H
# define ASM_H

# include "asm_op.h"
# include "op.h"

typedef unsigned short	t_2b;
//typedef unsigned int	t_4b;
//typedef unsigned long	t_8b;

# define REGISTER		(t_2b)0b100000000000
# define DIRECT			(t_2b)0b010000000000
# define DIRECT_LABEL	(t_2b)0b001000000000
# define INDIRECT		(t_2b)0b000100000000
# define INDIRECT_LABEL	(t_2b)0b000010000000
# define COMMAND		(t_2b)0b000001000000
# define STRING			(t_2b)0b000000100000
# define LABEL			(t_2b)0b000000010000
# define INSTRUCTION	(t_2b)0b000000001000
# define SEPARATOR		(t_2b)0b000000000100
# define NEW_LINE		(t_2b)0b000000000010
# define END			(t_2b)0b000000000001



typedef struct s_token	t_token;
struct				s_token
{
	char			*label;
	t_op			*op;//fill in join_token
	char			*hex_str;//fill in parse_op
	int				status;//-1_-2_0_1
	int				offset;//относит начала exec code
	int				num_byte_op;//fill in parse_op

	t_token			*next;
	t_token			*prev;


};

typedef struct s_data	t_data;
struct				s_data
{
	t_header		*header;
	t_token			*tkn_lst;
	int				fd_s;
	int				fd_cor;
	int				namelen;
	int				commlen;
	u_int64_t		exec_bytes
};

typedef struct s_lbl_lst	t_lbl_lst;
struct				s_lbl_lst
{
	char			*label;
	u_int64_t		offset;//относит начала exec code

	t_lbl_lst		*next;
};


/*
** error.c
*/
void			error(void);
void			syntax_err(int token);


/*
** twrite_bytes.c
*/
void			int_to_hex(int32_t dec, int dir_size, u_int32_t *place);


/*
** tokenize.c
*/
t_token			*new_token();
void			need_address_label(t_token *new);
void			parse_op(char *op);
t_token			*join_token(t_2b token_type, int indx_op);
int				add_token(char *s, int size, t_2b token_type, int indx_op);


/*
** parse_str.c
*/
t_lbl_lst		*add_lbl(char *s, const int size);
char			*skip_space(char *s);
char			*skip_comment(char *s);
void			solve_res(char *s, char *op, int a);
int				search_op(char *s);
void			tokenize(char *s);
int				parse_str(char **buf);

/*
** main.c
*/
int					valid_filename(char *filename);
int					parse_file(int fd_s);
int					data_malloc();
void				read_file(char *filename);

void				error(void);

#endif

