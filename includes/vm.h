#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include "op.h"
# include "../libft_clala/includes/ft_printf.h"
# include "../libft_clala/includes/libft.h"
# include "vm_error.h"

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

typedef struct			s_op
{
	char				*name;
	int					arg_count;
	int					arr[3];
	int					index;
	int					loop;
	char				*description;
	int					arg_type;
	int					dir_size;
}						t_op;

extern t_op				g_op_tab[17];

typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	unsigned int		code_size;
	char				*code;
	struct s_player		*next;
}						t_player;

typedef struct 		s_players
{
	int				qty;
	struct s_player	*first_player;
	int				last_alive_num;
	size_t			lives_num;
}					t_players;

typedef struct 			s_mods
{	
	ssize_t				dump_cycle;
	int					dump_size;
	ssize_t				show_cycle;
	int					show_print_mode;
	bool				aff;
	int					log;
}						t_mods;

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

typedef struct			s_vs
{
	
}						t_vs;

typedef struct			s_carriage
{
	struct s_carriage	*next;
	struct s_carriage	*prev;		
	int					num;
	int					carry;
	int					regs[REG_NUMBER];
	int					pos;
	int					opcode;
	int					live_cycle;
	int					cycles_countdown;
	int					last_cycle_alive;
}						t_carriage;

typedef struct			s_carriages
{
	struct s_carriage	*head;
	struct s_carriage	*tail;
	int					qty;
	int					nums;
}						t_carriages;

typedef struct			s_vm
{
	struct s_vm_info	*data;
	struct s_players	*players;

	struct s_carriages	*carr;	
	struct s_vs			*vs;					
	struct s_mods		*mods;
	t_op				op_tab[17];
	void				(*exec[17])(t_carriage *curr, struct s_vm *vm);
}						t_vm;

// op_code fucntions
void	handle_carriages(t_vm *vm);
void				game(t_player *players[], t_vm *vm);
void				display_memory(char *arena);
//void				state_opcode(t_carriage *curr, t_vm *vm);
//void				exec_op(t_carriage *curr, t_vm *vm);

unsigned char		*get_args(char arg_code, unsigned char arr[4]);
int					check_args(int *step, unsigned char *args, t_carriage *curr,
								t_vm *vm);
int					get_int(int *pos, t_carriage *curr,
								t_vm *vm, int size);
void				set_int(int *pos, int num, t_vm *vm);
void				check_position(int *pos, t_vm *vm);
int					get_one_arg(int *temp, unsigned char code,
									t_carriage *curr, t_vm *vm);
int					get_one_arg_no_md(int *temp, unsigned char code,
									t_carriage *curr, t_vm *vm);
void				increase_position(int *pos, int delta);

void				live(t_carriage *curr, t_vm *vm);
void				ld(t_carriage *curr, t_vm *vm);
void				st(t_carriage *curr, t_vm *vm);
void				add(t_carriage *curr, t_vm *vm);
void				sub(t_carriage *curr, t_vm *vm);
void				and(t_carriage *curr, t_vm *vm);
void				or(t_carriage *curr, t_vm *vm);
void				xor(t_carriage *curr, t_vm *vm);
void				zjmp(t_carriage *curr, t_vm *vm);
void				ldi(t_carriage *curr, t_vm *vm);
void				sti(t_carriage *curr, t_vm *vm);
void				cwfork(t_carriage *curr, t_vm *vm);
void				lld(t_carriage *curr, t_vm *vm);
void				lldi(t_carriage *curr, t_vm *vm);
void				lfork(t_carriage *curr, t_vm *vm);
void				aff(t_carriage *curr, t_vm *vm);
void				test_display(char*arena);
void				delete_old_carriage(t_vm *vm);
void				display_arena(t_vm *vm);

// END OP_CODE













/*
** t_players functions
*/
t_players	*t_players_new(void);
t_player	*t_players_add_new_player(t_players *players, int number, t_vm *vm);
void handle_players(t_vm *vm, t_players *players);
t_player *get_player_by_number(t_players *players, int num);

/*
** t_players functions
*/
t_player			*t_player_create(int number, t_vm *vm);

/*
** errors handling
*/
int					handle_error(char *s);
int					handle_error_vm(char *error_message, t_vm *vm);
int					handle_error_str_arg(char *error_message, char *arg, t_vm *vm);
int					handle_error_int_arg(char *error_message, int arg, t_vm *vm);
int					print_usage(void);

/*
** t_vm_info
*/
t_vm_info			*t_vm_info_new(void);

/*
** t_carriage and t_carriages
*/
t_carriage			*t_carriage_new(t_carriages *carr, int pos);
t_carriage			*t_carriages_insert_after(t_carriages *list,
							t_carriage *node, t_carriage *new);
t_carriage			*t_carriages_insert_before(t_carriages *list,
							t_carriage *node, t_carriage *new);
t_carriage			*t_carriages_push(t_carriages *list, t_carriage *new);
t_carriage			*t_carriages_append(t_carriages *list, t_carriage *new);
t_carriages			*t_carriages_new();
t_carriage			*t_carriages_pop(t_carriages *list, t_carriage *node);
t_carriages			*t_carriages_remove_node(t_carriages *list, t_carriage *node);
int					*get_nums(t_carriages *carrs);
t_carriage		*t_carriage_copy(t_carriages *carr, t_carriage *src);

/*
** Validation
*/
void	parse_args(t_vm *vm, int ac, char **av);
int	parse_player(t_vm *vm, char *arg, t_player *player);
int	is_integer(char *s);

/*
** vm, vsm mods create
*/
t_vm		*t_vm_create(void);
t_vs		*t_vs_create(t_vm *vm);
t_mods *t_mods_create(t_vm *vm);

/*
** print functions
*/
void print_t_player(t_player *player);
void print_t_players(t_players *players);
void	print_t_carriage(t_carriage *carriage);
void	print_t_carriages(t_carriages *carriages);
void		print_introduction(t_players *players);
void	print_last_alive(t_vm *vm);
void		print_is_alive(int num, char *player_name);
int		print_dump(t_vm *vm);
void		print_final_result(t_vm *vm);

#endif