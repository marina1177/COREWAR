
#ifndef COM_H
# define COM_H

# define TRUE 1
# define FALSE 0

# include "../libft/includes/libft.h"
//# include "asm_op.h"
# include "asm_error.h"

//# include "op.h"
//# include "asm.h"


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


/* ************************************************************************** */
/*                                                                            */
/*                                                        ...      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* ************************************************************************** */

typedef unsigned char	t_1b;
typedef unsigned short	t_2b;
typedef unsigned int	t_4b;
typedef unsigned long	t_8b;

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

# define EXEC_START (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
# define FULL_SIZE (EXEC_START + CHAMP_MAX_SIZE)

/*
**
*/

# define EOC	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define WHITE	"\033[1;37m"
# define BLACK	"\033[0;30m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define PURPUL	"\033[0;35m"
# define CYAN	"\033[0;36m"

# define IS_BLANK(c) (c == ' ' || c == '\t')
# define IS_ENDLINE(c) (c == '\n' || c == '\0')
//typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8


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
/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3




typedef struct		s_header t_header;
struct				s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
};

typedef struct s_op	t_op;

struct				s_op
{
	char			*name;
	unsigned int	code;
	u_int16_t		args_num;
	u_int8_t		args_types_code;
	unsigned int	args_types[3];
	unsigned int	t_dir_size;
};

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
	//char			**op_args;
	//t_2b			args_type[3];
	//int32_t			status;//-1_-2_0_1
	int32_t			offset;//относит начала exec code
	int32_t			num_byte_op;//fill in parse_op

	t_token			*next;
	t_token			*prev;
};

typedef struct s_data	t_data;
struct				s_data
{
	int					x;
	int					y;
	t_op			*g_op_tab;
	char			*filename;
	t_header		*head;
	//t_token			*tkn_lst;
	int				fd_s;
	//int				fd_cor;
	t_4b			name_f;
	t_4b			comm_f;
	unsigned long	namelen;
	unsigned long	commlen;
	int64_t		exec_bytes;
};

typedef struct s_lbl_lst	t_lbl_lst;
struct				s_lbl_lst
{
	char			*label;
	int32_t			offset;//относит начала exec code
	t_2b			new_line;
	t_lbl_lst		*next;
};

//********************************************************************************
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_op.h                                           :+:      :+:    :+:   */
/* ************************************************************************** */



static t_op			g_op_tab[16] = {
	{
			.name = "live",
			.code = 0x01,
			.args_num = 1,
			.args_types_code = FALSE,
			.args_types = {T_DIR, 0, 0},
			.t_dir_size = 4,
	},
	{
			.name = "ld",
			.code = 0x02,
			.args_num = 2,
			.args_types_code = TRUE,
			.args_types = {T_DIR | T_IND, T_REG, 0},
			.t_dir_size = 4,
	},
	{
			.name = "st",
			.code = 0x03,
			.args_num = 2,
			.args_types_code = TRUE,
			.args_types = {T_REG, T_REG | T_IND, 0},
			.t_dir_size = 4,
	},
	{
			.name = "add",
			.code = 0x04,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG, T_REG, T_REG},
			.t_dir_size = 4,
	},
	{
			.name = "sub",
			.code = 0x05,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG, T_REG, T_REG},
			.t_dir_size = 4,
	},
	{
			.code = 0x06,
			.name = "and",
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
			.t_dir_size = 4,
	},
	{
			.name = "or",
			.code = 0x07,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
			.t_dir_size = 4,
	},
	{
			.name = "xor",
			.code = 0x08,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
			.t_dir_size = 4,
	},
	{
			.name = "zjmp",
			.code = 0x09,
			.args_num = 1,
			.args_types_code = FALSE,
			.args_types = {T_DIR, 0, 0},
			.t_dir_size = 2,
	},
	{
			.name = "ldi",
			.code = 0x0A,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
			.t_dir_size = 2,
	},
	{
			.name = "sti",
			.code = 0x0B,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
			.t_dir_size = 2,
	},
	{
			.name = "fork",
			.code = 0x0C,
			.args_num = 1,
			.args_types_code = FALSE,
			.args_types = {T_DIR, 0, 0},
			.t_dir_size = 2,
	},
	{
			.name = "lld",
			.code = 0x0D,
			.args_num = 2,
			.args_types_code = TRUE,
			.args_types = {T_DIR | T_IND, T_REG, 0},
			.t_dir_size = 4,
	},
	{
			.name = "lldi",
			.code = 0x0E,
			.args_num = 3,
			.args_types_code = TRUE,
			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
			.t_dir_size = 2,
	},
	{
			.name = "lfork",
			.code = 0x0F,
			.args_num = 1,
			.args_types_code = FALSE,
			.args_types = {T_DIR, 0, 0},
			.t_dir_size = 2,
	},
	{
			.name = "aff",
			.code = 0x10,
			.args_num = 1,
			.args_types_code = TRUE,
			.args_types = {T_REG, 0, 0},
			.t_dir_size = 4,
	}
};
//*****************************************************************************************
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/* ************************************************************************** */

void	print_memory(const void *addr, size_t size);

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
char			*skip_space(char *s);
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
** get_args.c
*/
t_opargs		*parse_parameter(char *line);
void			get_args(char *line);

/*
** asm_3.c
*/
int				is_lblchar(char c);
int				check_same_name(char *s, char **s_op, int a);


/*
** parse_op.c
*/
void			parse_op(char *line);
int				search_op(char *line);
t_token			*new_token();
void			add_token(char *line,  int indx_op);
void			check_op(char *line);

/*
** check_label.c
*/
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
int			get_line(const int fd, char **row);

/*
** main.c
*/
void				valid_filename(char *filename);
void				data_init();
void				read_file(char *filename, int flag);

void				error(void);


char		g_name[128];
char		g_comment[2048];
size_t		g_snum;//num line
size_t		g_rnum;//x
t_data		*g_data;
//t_header	*g_head;

t_token		*g_tkn_first;
t_token		*g_tkn_last;

t_lbl_lst	*g_label_first;
t_lbl_lst	*g_label_last;
u_int64_t	g_offset;//отн начала файла
char		*g_buf;



#endif
