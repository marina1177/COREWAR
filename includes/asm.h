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

# include "com.h"
# include "asm_op.h"
# include "asm_error.h"

typedef unsigned char	t_1b;
typedef unsigned short	t_2b;
typedef unsigned int	t_4b;
typedef unsigned long	t_8b;

# define REGISTER		(t_2b)0b10000000000000
# define DIRECT			(t_2b)0b01000000000000
# define DIRECT_LABEL	(t_2b)0b00100000000000
# define INDIRECT		(t_2b)0b00010000000000
# define INDIRECT_LABEL	(t_2b)0b00001000000000
# define COMMAND		(t_2b)0b00000100000000
# define STRING			(t_2b)0b00000010000000
# define LABEL			(t_2b)0b00000001000000
# define INSTRUCTION	(t_2b)0b00000000100000
# define SEPARATOR		(t_2b)0b00000000010000
# define NEW_LINE		(t_2b)0b00000000001000
# define END			(t_2b)0b00000000000100
# define NAME			(t_2b)0b00000000000010
# define COMMENT		(t_2b)0b00000000000001


typedef struct s_opargs	t_opargs;
struct				s_opargs
{
	int				x;
	int				y;
	char			*arg;
	int32_t			argsize;
	t_2b			argtype;
	int				value;
};

typedef struct s_token	t_token;
struct				s_token
{
	int				x;
	int				y;
	t_2b			new_line;
	t_op			*op;
	t_opargs		*args[3];
	int32_t			offset;
	int32_t			num_byte_op;
	t_token			*next;
	t_token			*prev;
};

typedef struct s_data	t_data;
struct				s_data
{
	int				x;
	int				y;
	t_op			*g_op_tab;
	char			*filename;
	t_header		*head;
	int				fd_s;
	t_4b			name_f;
	t_4b			comm_f;
	unsigned long	namelen;
	unsigned long	commlen;
	int64_t			exec_bytes;
};

typedef struct s_lbl_lst	t_lbl_lst;
struct				s_lbl_lst
{
	char			*label;
	int32_t			offset;
	t_2b			new_line;
	t_lbl_lst		*next;
};


void			check_empty_file();
int				my_atoi(const char *str);
void			print_memory(const void *addr, size_t size);

/*
** supfun_2.c.c
*/
int				ft_findchar(char *str, int c);
int				ft_strmerge(char **dest, char **srcs);

/*
** supfun.c
*/
void			print_bits(size_t size, void *ptr, char space);
int32_t			ft_atoi_cor(const char *str, u_int8_t size);
void			skip_space(char *s);
char			*skip_comment(char *s);

/*
** write_to_file.c
*/
void			write_to_file(void);

/*
** translate.c
*/
void			int_to_hex(int32_t dec, int dir_size, u_int32_t *place);
void			print_champion_info();
void			print_instruction(t_token **op, u_int32_t *cursor, u_int8_t type);
void			translate(void);

/*
** free_data.c
*/
char			*freesplit();
void			free_token();
void			free_label();
void			free_data(void);

/*
** error.c
*/
void			put_error(char *err, int type);
void			print_error(char *message);
void			error_line(char *event, char *line, int x);
void			error_event(char *event);

void			error(void);

/*
** args_type.c
*/
int				check_reg(char *line, int size, u_int16_t i);
int				check_dir(char *line, int size, u_int16_t i);
int				check_ind(char *line, int size, u_int16_t i);
void			parse_args_type(u_int16_t i, char *line);

/*
** is_type.c
*/
int				is_reg(char *line, int len);
int				is_direct(char *line, int len);
int				is_dir_label(char *line, int len);
int				is_indirect(char *line, int len);
int				is_ind_label(char *line, int len);

void			int_to_hex(int32_t dec, int dir_size, u_int32_t *place);

/*
** parse_args.c
*/
t_opargs		*parse_parameter(char *line);
void			parse_args(char *line);

int				is_lblchar(char c);

/*
** parse_op.c
*/
void			parse_op(char *line);
int				search_op(char *line);
t_token			*new_token();
void			add_token(int indx_op);
void			check_op(char *line);

/*
** check_label.c
*/
void			check_dup_label();
void			check_new_line(char *line, int f);
void			add_lbl(char *s, size_t size);
void			check_label(char *line);

/*
** add_header.c
*/
void			valid_headlen(t_2b type_h, int len);
void			put_header(char *str, int len, t_2b type_h);
void			process_header(char **line, t_2b type_h);
t_2b			exist_header(char **line);
void			add_header(char **line);

/*
** parse_file.c
*/
void			parse_str(char **line);
void			parse_file();

/*
** get_line.c
*/
int					get_line(const int fd, char **row);

/*
** main.c
*/
void				valid_filename(char *fname);
void				data_init();
void				read_file(char *filename);

void				error(void);


char		g_name[128];
char		g_comment[2048];
t_data		*g_data;
//t_header	*g_head;

t_token		*g_tkn_first;
t_token		*g_tkn_last;

t_lbl_lst	*g_label_first;
t_lbl_lst	*g_label_last;
u_int64_t	g_offset;//отн начала файла
char		*g_buf;


#endif

