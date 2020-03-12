
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

//typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8


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
	unsigned int	args_num;
	u_int8_t		args_types_code;
	unsigned int	args_types[3];
	unsigned int	t_dir_size;
};

typedef struct s_token	t_token;
struct				s_token
{
	//char			*label;
	t_op			*op;//fill in join_token
	char			**op_args;
	t_2b			args_type[3];//fill in parse_op
	int				status;//-1_-2_0_1
	int				offset;//относит начала exec code
	int				num_byte_op;//fill in parse_op

	t_token			*next;
	t_token			*prev;
};

typedef struct s_data	t_data;
struct				s_data
{
	t_op			*g_op_tab;
	char			*filename;
	t_header		*head;
	//t_token			*tkn_lst;
	int				fd_s;
	int				fd_cor;
	t_4b			name_f;
	t_4b			comm_f;
	unsigned long	namelen;
	unsigned long	commlen;
	u_int64_t		exec_bytes;
};

typedef struct s_lbl_lst	t_lbl_lst;
struct				s_lbl_lst
{
	char			*label;
	u_int64_t		offset;//относит начала exec code

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


/*
** supfun.c.c
*/
void			print_bits(size_t size, void *ptr, char space);
char			*skip_space(char *s);
char			*skip_comment(char *s);

/*
** translate.c
*/
void			int_to_hex(int32_t dec, int dir_size, u_int32_t *place);
t_token			*print_champion_info();
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
void			print_error(char *message);
void			error_line(char *event, char *line, int x);
void			error_event(char *event);

void			error(void);


/*
** is_type.c
*/
int				is_reg(char *line);
int				is_direct(char *line);
int				is_dir_label(char *line);
int				is_indirect(char *line);
int				is_ind_label(char *line);

//void			int_to_hex(int32_t dec, int dir_size, u_int32_t *place);
/*
** asm_3.c
*/
void			parse_args_type();
void			parse_op(char *op);
int				is_lblchar(char c);
void			solve_res(char *s, char **s_op, int a);
int				check_same_name(char *s, char **s_op, int a);
void			search_op(char *s);

/*
** asm_2.c
*/
void			need_address_label(t_token *new);


t_token			*new_token();
t_token			*join_token( int indx_op);
int				add_token(char *s, int size, t_2b token_type, int indx_op);
void			add_lbl(char *s, const int size);




void			save_head(char *p, t_4b type_h, t_4b *flg, unsigned long *len );
char			*init_headdata(char *p, t_4b *flg);
void			add_header(char *s);

void			parse_str(char **buf);

/*
** main.c
*/
void				valid_filename(char *filename);
void				parse_file(int fd_s);
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
