#ifndef VM_H
# define VM_H

# include "asm_error.h"
# include "../libft/includes/libft.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

#define REG_NUMBER				16
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

# define RUNNING 			713
# define CYCLE_PER_SEC		1225
# define CYCLE_COORD		1993
# define PROCESSES			2505
# define PL_ONE_LIVE		3529

# define LIVE_CODE	0x01
# define LD_CODE 	0x02
# define ST_CODE	0x03
# define ADD_CODE	0x04
# define SUB_CODE	0x05
# define AND_CODE	0x06
# define OR_CODE	0x07
# define XOR_CODE	0x08
# define ZJMP_CODE	0x09
# define LDI_CODE	0x0a
# define STI_CODE	0x0b
# define FORK_CODE	0x0c
# define LLD_CODE	0x0d
# define LLDI_CODE	0x0e
# define LFORK_CODE	0x0f
# define AFF_CODE	0x10

# define LIVE_CYCLE_CD	10
# define LD_CYCLE_CD	5
# define ST_CYCLE_CD	5
# define ADD_CYCLE_CD	10
# define SUB_CYCLE_CD	10
# define AND_CYCLE_CD	6
# define OR_CYCLE_CD	6
# define XOR_CYCLE_CD	6
# define ZJMP_CYCLE_CD	20
# define LDI_CYCLE_CD	25
# define STI_CYCLE_CD	25
# define FORK_CYCLE_CD	800
# define LLD_CYCLE_CD	10
# define LLDI_CYCLE_CD	50
# define LFORK_CYCLE_CD	1000
# define AFF_CYCLE_CD	2

#define T_REG					1
#define T_DIR					2
#define T_IND					4

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE

typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					exec_size;
	char				*exec;
	unsigned int		position;
}						t_player;

typedef	struct			s_carriage
{
	unsigned int		position;
	int					last_cycle_alive;
	char				op_code;
	int					circles;
	int					num_of_carriage;
	int					carry;
	int					regs[REG_NUMBER + 1];

	struct s_carriage	*next;
	// struct s_carriage	*prev;
}						t_carriage;

typedef struct			s_vm_info
{
	uint8_t				arena[MEM_SIZE];
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	int					checks_counter;
	int					lives_counter;
}						t_vm_info;

typedef struct 			s_mods
{
	ssize_t				dump_cycle;
	int					dump_size;
	ssize_t				show_cycle;
	int					show_print_mode;
	bool				aff;
	int					log;
}						t_mods;

typedef	struct	s_vm
{
	unsigned char	*arena;
	t_vm_info		*data;
	t_player		*players;
	t_carriage		*carriages;
	t_mods			*mods;
}				t_vm;

typedef	struct			s_bit
{
	unsigned		forth : 2;
	unsigned		third : 2;
	unsigned		second : 2;
	unsigned		first : 2;
}						t_bit;

typedef	union			s_arg_types
{
	unsigned char	types;
	t_bit			bit;
}						t_arg_types;

void	init(t_vm *data, int quantity);
void	init_arena(t_vm *data, int quantity);
void	read_data(char *filename, t_player *player);
void	ft_exit(char *line);
void	clean_data(t_vm *data);
void	test(int op, unsigned char *arena); //delete
void	print_byte(unsigned char c); //delete
void	print_memory(const void *addr, size_t size);
int		check_operation(unsigned char *arena, t_carriage *carriage, unsigned char *arguments);
void	change_position(unsigned int *position, int change);
int		get_num_from_char(unsigned char *arena,  unsigned int position, int size);
int		get_arg_size(int op, unsigned char arg);
void	write_reg(unsigned char *arena, int reg,  unsigned int position, int change);
int		get_arg_value(unsigned char *arena, t_carriage *car,  unsigned int *pos, char arg_type);
int		get_reg_value(unsigned char *arena, unsigned int *pos);

t_carriage	*make_new_carriage(unsigned int position);
void		add_carriage(t_carriage **head, t_carriage *new);
void		del_carriage(t_carriage **head, t_carriage *carriage);

void	(*actions[17])();
void	do_live(t_carriage *carriage, t_vm *vm);
void	do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_zjmp(t_carriage *carriage, t_vm *vm);
void	do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_sti(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_fork(t_carriage *carriage, t_vm *vm);
void	do_lld(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_lldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void	do_lfork(t_carriage *carriage, t_vm *vm);
void	do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments);

typedef struct s_op	t_op;

struct				s_op
{
	char			*name;
	unsigned int	code;
	unsigned int	args_num;
	uint8_t		args_types_code;
	unsigned char	args_types[3];
	unsigned int	t_dir_size;
};

static t_op			g_op_tab[17] = {
	{},
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


#endif
