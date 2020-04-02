#include "../../includes/vm.h"
static void	init_carriages(t_vm *data, int quantity)
{
	t_carriage *new;
	unsigned int position;
	int i;

	i = 0;
	data->carriages = NULL;
	while (i < quantity)
	{
		position = data->players[i].position;
		new = make_new_carriage(position);
		new->regs[1] = -1 * (i + 1);
		add_carriage(&data->carriages, new);
		i++;
	}
}

static void	init_players(t_vm *data, int quantity)
{
	int i;
	t_player *player;

	i = 0;
	data->players = (t_player *)malloc(sizeof(t_player) * quantity);
	if (!data->players)
		ft_exit(ERR_ALLOC);
	while (i < quantity)
	{
		player = &data->players[i];
		player->num = 0;
		player->name = NULL;
		player->comment = NULL;
		player->exec_size = 683;
		player->exec = NULL;
		player->position = MEM_SIZE / quantity * i;
		i++;
	}
}

static void	init_actions_array()
{
	actions[1] = do_live;
	actions[2] = do_ld;
	actions[3] = do_st;
	actions[4] = do_add;
	actions[5] = do_sub;
	actions[6] = do_and;
	actions[7] = do_or;
	actions[8] = do_xor;
	actions[9] = do_zjmp;
	actions[10] = do_ldi;
	actions[11] = do_sti;
	actions[12] = do_fork;
	actions[13] = do_lld;
	actions[14] = do_lldi;
	actions[15] = do_lfork;
	actions[16] = do_aff;
}

void	init_arena(t_vm *data, int quantity)
{
	int i;
	unsigned int position;
	i = 0;
	while(i < quantity)
	{
		position = data->players[i].position;
		ft_memcpy(&(data->arena[position]), data->players[i].exec, 683);
		ft_strdel(&(data->players[i].exec));
		i++;
	}
}

void	init(t_vm *data, int quantity)
{
	data->arena = (unsigned char *)malloc(sizeof(char) * MEM_SIZE);
	if (!data->arena)
		ft_exit(ERR_ALLOC);
	ft_bzero(data->arena, MEM_SIZE);
	init_players(data, quantity);
	init_carriages(data, quantity);
	init_actions_array();
}
