/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:15:54 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 22:15:54 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include "op.h"
# include "vs_consts.h"
# include "../libft_clala/includes/ft_printf.h"
# include "../libft_clala/includes/libft.h"
# include "vm_error.h"
# include <stdio.h>


# define RUNNING 			713
# define CYCLE_PER_SEC		1225
# define CYCLE_COORD		1993
# define PROCESSES			2505
# define PL_ONE_LIVE		3529
/*
**
*/
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
/*
**
*/
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
# define CYCLES_BEFORE_DUMP 1000
# define VERB_L0 0
# define VERB_L1 1
# define VERB_L2 2
# define VERB_L3 4
# define VERB_L4 8
# define VERB_L5 16

typedef struct			s_op
{
	char				*name;
	int					args_num;
	unsigned int		arr[3];
	int					index;
	int					loop;
	char				*description;
	int					arg_type;
	int					t_dir_size;
}						t_op;

extern t_op				g_op_tab[17];


typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					code_size;
	char				*code;
	struct s_player		*next;
	int					last_live;
	int					is_alive;
	int					start_code;
	int					lives_in_period;
}						t_player;

typedef struct 			s_players
{
	int					qty;
	struct s_player		*first_player;
	struct s_player		*last_player;
	int					last_alive_num;
	int					lives_num;
}						t_players;

typedef struct 			s_mods
{	
	int					dump_cycle;
	int					dump_size;
	int					verbosity_level;
	int					show_cycle;
	int					show_print_mode;
	int					aff;	
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
//***************************************************************

typedef struct			s_content
{
	char				**words;
	struct s_content	*next;

}						t_content;

typedef struct			s_json_item
{
	int					value;
	char				title[128];
	char				keys[9][128];
	//t_content			*content;

}						t_json_item;

typedef struct			s_vs
{
	uint8_t				error_code;
	uint8_t				state_refresh;
	uint8_t				players_refresh;
	uint8_t				carriages_refresh;
	uint8_t				cells_refresh;

	uint64_t			const_begin_len;
	uint64_t			change_begin_len;
	struct s_json_item	vs_const[7];
	struct s_json_item	vs_change[9];
}						t_vs;

typedef struct			s_cells
{
	int					players_id;
	int					num_addr;
	int					cells_address[1000];
	struct s_cells		*last;
	struct s_cells		*next;
}						t_cells;


//********************************************************************
typedef struct			s_carriage
{
	struct s_carriage	*next;
	struct s_carriage	*prev;
	int					num;
	int					carry;
	int					regs[REG_NUMBER];
	int					pos;
	int					op_code;
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
	struct s_cells		*cells;
	struct s_mods		*mods;
	t_op				op_tab[17];
	void				(*exec[17])();
	//void				(*exec[17])(t_carriage *curr, struct s_vm *vm);
}						t_vm;

typedef	struct			s_bit
{
	unsigned			forth : 2;
	unsigned			third : 2;
	unsigned			second : 2;
	unsigned			first : 2;
}						t_bit;

typedef	union			s_arg_types
{
	unsigned char	types;
	t_bit			bit;
}						t_arg_types;

//*********************VS******************************************************

/*
** vs_refresh.c
*/
void		state_refresh(t_vm *vm);
void		players_refresh(t_vm *vm);
void		carriages_refresh(t_vm *vm);
void		cells_refresh(t_vm *vm);

/*
** vs_add_cells.c
*/
t_cells		*new_cells(t_cells **head, int	id);
t_cells		*find_id(t_cells **head, int id);
void		push_cells(t_vm *vm, int player_id, int	cell_number);

/*
** vs_package.c
*/
char	*put_atom_const(t_vm *vm, char **buf);
char	*put_array_const(t_vm *vm, char **buf);
void	put_buf(t_vm *vm, int type, char **buf);
void	print_vs(t_vm	*vm, int type);

/*
** vs_put_change.c
*/
char		*put_cells(t_vm *vm, char **buf);
char		*put_carriages(t_vm *vm, char **buf);
char		*put_players(t_vm *vm, char **buf);
char		*put_state(t_vm *vm, char **buf);

/*
** vs_utilites.c
*/
int			count_dig(size_t val);
int			vs_putstr_fd(char const *s, int fd);
int			vs_strcpy(char *dest, const char *src);
uint64_t	calculate_buf(t_vm *vm, int type);

int			vs_itoa(int n, char *s);
//****************************************************************************

void					init(t_vm *data, int quantity);
void					init_arena(t_vm *data, int quantity);
void					read_data(char *filename, t_player *player);
void					ft_exit(char *line);
void					clean_data(t_vm *data);
void					test(int op, unsigned char *arena);
void					print_byte(unsigned char c);
void					print_memory(const void *addr, size_t size);
int						check_operation(unsigned char *arena, t_carriage *carriage, unsigned char *arguments);
int						valid_operation_code(t_carriage *carriage);
void					make_operation(t_vm *vm, t_carriage *carriage, unsigned char *arguments);
void					change_position(int *position, int change);
int						get_num_from_char(unsigned char *arena,  int position, int size);
int						get_negative_number(void *argument, int size);
int						get_arg_size(int op, unsigned char arg);
void					write_reg(unsigned char *arena, int reg,  int position, int change);
int						get_arg_value(unsigned char *arena, t_carriage *car,  int *pos, char arg_type);
int						get_reg_value(unsigned char *arena, int *pos);
t_carriage				*make_new_carriage(unsigned int position);
void					add_carriage(t_carriage **head, t_carriage *new);
void					del_carriage(t_carriage **head, t_carriage *carriage);
void					(*actions[17])();
void					do_live(t_carriage *carriage, t_vm *vm);
void					do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_and(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_or(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_xor(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_zjmp(t_carriage *carriage, t_vm *vm);
void					do_ldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_sti(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_fork(t_carriage *carriage, t_vm *vm);
void					do_lld(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_lldi(t_carriage *carriage, t_vm *vm, unsigned char *arguments);
void					do_lfork(t_carriage *carriage, t_vm *vm);
void					do_aff(t_carriage *carriage, t_vm *vm, unsigned char *arguments);

/*
**	op_code fucntions
*/
void					handle_carriages(t_vm *vm);
void					game(t_player *players[], t_vm *vm);
void					display_memory(char *arena);
int						exec_op(t_carriage *carriage, t_vm *vm);

unsigned char			*get_args(char arg_code, unsigned char arr[4]);
int						check_args(int *step, unsigned char *args, t_carriage *curr,
								t_vm *vm);
int						get_int(int *pos, t_carriage *curr,
								t_vm *vm, int size);
void					set_int(int *pos, int num, t_vm *vm);
void					check_position(int *pos, t_vm *vm);
int						get_one_arg(int *temp, unsigned char code,
									t_carriage *curr, t_vm *vm);
int						get_one_arg_no_md(int *temp, unsigned char code,
									t_carriage *curr, t_vm *vm);
void					increase_position(int *pos, int delta);
void					test_display(char*arena);
void					delete_old_carriage(t_vm *vm);
void					display_arena(t_vm *vm);

// END OP_CODE

/*
** t_players functions
*/
t_players				*t_players_new(void);
t_player				*t_players_add(t_players *players, int number, t_vm *vm);
void					handle_players(t_vm *vm, t_players *players);
t_player				*get_player_by_number(t_players *players, int num);
int						t_players_get_next_number(t_players *players);

/*
** t_players functions
*/
t_player				*t_player_create(int number, t_vm *vm);

/*
** errors handling
*/
int						handle_error(char *s);
int						handle_error_vm(char *error_message, t_vm *vm);
int						handle_error_str_arg(char *error_message, char *arg, t_vm *vm);
int						handle_error_int_arg(char *error_message, int arg, t_vm *vm);
int						print_usage(void);


/*
** t_carriage and t_carriages
*/
t_carriage				*t_carriage_new(t_carriages *carr, int pos);
t_carriage				*t_carriages_insert_after(t_carriages *list,
							t_carriage *node, t_carriage *new);
t_carriage				*t_carriages_insert_before(t_carriages *list,
							t_carriage *node, t_carriage *new);
t_carriage				*t_carriages_push(t_carriages *list, t_carriage *new);
t_carriages				*t_carriages_create(t_vm *vm);
t_carriage				*t_carriages_pop(t_carriages *list, t_carriage *node);
t_carriages				*t_carriages_remove_node(t_carriages *list, t_carriage *node);
int						*get_nums(t_carriages *carrs);
t_carriage				*t_carriage_copy(t_carriages *carr, t_carriage *src);

/*
** Validation
*/
void					parse_args(t_vm *vm, int ac, char **av);
int						parse_player(t_vm *vm, char *arg, t_player *player);
int						is_integer(char *s);

/*
** vm, vsm mods create
*/
t_vm					*t_vm_create(void);
t_vs					*t_vs_create(t_vm *vm);
t_mods					*t_mods_create(t_vm *vm);
t_vm_info				*t_vm_info_create(t_vm *vm);

/*
** print functions
*/
void					print_t_player(t_player *player);
void					print_t_players(t_players *players);
void					print_t_carriage(t_carriage *carriage);
void					print_t_carriages(t_carriages *carriages);
void					print_introduction(t_players *players);
int						print_is_alive(int num, char *player_name);
int						print_dump(t_vm *vm, int dump_size);
void					print_final_result(t_vm *vm);
void					print_sti(unsigned char *arguments, int temp,
							int *values, int reg);
void					print_st(t_carriage *carriage, int reg, int *values, int temp_val);
void					print_live(t_vm *vm, t_carriage *carriage, int num);
void					print_lld(t_carriage *carriage, unsigned char *arguments, int *values);
void					print_ldi(t_carriage *carriage,
							unsigned char *arguments, int *values, int temp_pos);
void					print_lldi(t_carriage *carriage, unsigned char *arguments,
							int *values, int temp_pos);
void					print_bitwise_op(t_vm *vm,
							t_carriage *carriage, int *values);
void					print_move(t_vm *vm, t_carriage *carriage, int temp_pos);

#endif
