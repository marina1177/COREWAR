#ifndef VM_H
# define VM_H

# include "op.h"
# include "../libft/includes/ft_printf.h"
# include <fcntl.h>


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

// static t_op			g_op_tab[16] = {
// 	{
// 			.name = "live",
// 			.code = 0x01,
// 			.args_num = 1,
// 			.args_types_code = FALSE,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "ld",
// 			.code = 0x02,
// 			.args_num = 2,
// 			.args_types_code = TRUE,
// 			.args_types = {T_DIR | T_IND, T_REG, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "st",
// 			.code = 0x03,
// 			.args_num = 2,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG, T_REG | T_IND, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "add",
// 			.code = 0x04,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG, T_REG, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "sub",
// 			.code = 0x05,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG, T_REG, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.code = 0x06,
// 			.name = "and",
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "or",
// 			.code = 0x07,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "xor",
// 			.code = 0x08,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "zjmp",
// 			.code = 0x09,
// 			.args_num = 1,
// 			.args_types_code = FALSE,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "ldi",
// 			.code = 0x0A,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "sti",
// 			.code = 0x0B,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "fork",
// 			.code = 0x0C,
// 			.args_num = 1,
// 			.args_types_code = FALSE,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "lld",
// 			.code = 0x0D,
// 			.args_num = 2,
// 			.args_types_code = TRUE,
// 			.args_types = {T_DIR | T_IND, T_REG, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "lldi",
// 			.code = 0x0E,
// 			.args_num = 3,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "lfork",
// 			.code = 0x0F,
// 			.args_num = 1,
// 			.args_types_code = FALSE,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "aff",
// 			.code = 0x10,
// 			.args_num = 1,
// 			.args_types_code = TRUE,
// 			.args_types = {T_REG, 0, 0},
// 			.t_dir_size = 4,
// 	}
// };

typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					code_size;
	char				*code;
}						t_player;


typedef	struct			s_carriage
{
	int					num_of_carriage;
	int					carry;
	int					regs[REG_NUMBER];

	struct s_carriage	*next;
	struct s_carriage	*prev;
}						t_carriage;
#endif


/*
//структура бражника (для сравнения)

typedef struct			s_vm
{
	uint8_t				arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];  // Players
	int32_t				players_num;			// Players
	t_player			*last_alive;			// Players
	t_cursor			*cursors;				// Cursors
	size_t				cursors_num;			// Cursors
	size_t				lives_num;				// Players
	ssize_t				cycles;					// vm	
	ssize_t				cycles_to_die;			// vm
	ssize_t				cycles_after_check;		// vm
	size_t				checks_num;				// vm
	struct s_vs			*vs;					// vm
	ssize_t				dump_cycle;				// modes
	int					dump_print_mode;		// modes
	ssize_t				show_cycle;				// modes
	int					show_print_mode;		// modes
	t_bool				display_aff;			// modes
	int					log;					// modes
}						t_vm;
*/

/*
 вот что я предлагаю
 */

typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					code_size;
	char				*code;
	struct s_player		*next;
}						t_player;

typedef struct 		s_players
{
	int				qty;				// кол-во игроков	 			
	struct s_player	*first_player; 		//массив указателей на игроков
	struct s_player *last_alive;		// последний живой игрок
	size_t			lives_num;          // число жизней, относится к игрокам
}					t_players;

typedef struct 			s_carriages
{
	struct s_carriage	*carriage;
	int					carriage_num;
}						t_carriages;

typedef struct 			s_mods
{
	/* 
	 здесь все показатели по модам вывода
	 */
	ssize_t				dump_cycle;				// mods
	int					dump_print_mode;		// mods
	ssize_t				show_cycle;				// mods
	int					show_print_mode;		// mods
	bool				display_aff;			// mods
	int					log;					// mods
}						t_mods;

typedef struct			s_vm_info
{
	//данные арены и работы вм
	uint8_t				arena[MEM_SIZE];
	ssize_t				cycles;					// vm	
	ssize_t				cycles_to_die;			// vm
	ssize_t				cycles_after_check;		// vm
	size_t				checks_num;				// vm
}						t_vm_info;

typedef struct			s_vs
{
	
}						t_vs;

//вм структура будет выглядеть вот так

typedef struct			s_vm
{
	struct s_data		*data;
	struct s_players	*players;
	struct s_carriages	*carr;	
	struct s_vs			*vs;					
	struct s_mods		*mods;	
}						t_vm;

/*
** t_players functions
*/
t_players *t_players_new(void);
t_player *t_players_add_new_player(t_players *players, int number, t_vm *vm);

/*
** t_players functions
*/
t_player *t_player_create(int number, t_vm *vm);

/*
** errors handling
*/
int		handle_error(char *s);
int		handle_error_vm(char *error_message, t_vm *vm);