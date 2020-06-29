#include "../../includes/vm.h"

void	put_atom_const(t_vm *vm)
{
	vs_putstr_fd(vm->vs->fd, "\n\t\"Consts\": {\n\t\t\"mem_size\": ");
	vs_itoa_fd(vm->vs->fd, MEM_SIZE);
	vs_putstr_fd(vm->vs->fd, A_CYCLEDELTA);
	vs_itoa_fd(vm->vs->fd, CYCLE_DELTA);
	vs_putstr_fd(vm->vs->fd, A_PLAYERS_NUM);
	vs_itoa_fd(vm->vs->fd, vm->players->qty);
	vs_putstr_fd(vm->vs->fd, A_MAXCHECKS);
	vs_itoa_fd(vm->vs->fd, MAX_CHECKS);
	vs_putstr_fd(vm->vs->fd, A_C_NBR_LIVE);
	vs_itoa_fd(vm->vs->fd,NBR_LIVE);
	vs_putstr_fd(vm->vs->fd, A_C_CYCLE_TO_DIE);
	vs_itoa_fd(vm->vs->fd, CYCLE_TO_DIE);
}

void	put_array_const(t_vm *vm)
{
	t_player *tmp;

	vs_putstr_fd(vm->vs->fd, ",\n\t\t\"Players\": [");
	tmp = vm->players->first_player;
	while(tmp)
	{
		vs_putstr_fd(vm->vs->fd, "\n\t\t{");
		vs_putstr_fd(vm->vs->fd, A_C_ID);
		vs_itoa_fd(vm->vs->fd, tmp->num);
		vs_putstr_fd(vm->vs->fd, A_NAME);
		vs_putstr_fd(vm->vs->fd, "\"");
		vs_putstr_fd(vm->vs->fd, tmp->name);
		vs_putstr_fd(vm->vs->fd, "\"");
		vs_putstr_fd(vm->vs->fd, A_START_CODE);
		vs_itoa_fd(vm->vs->fd, tmp->start_code);
		vs_putstr_fd(vm->vs->fd, A_CODE_SIZE);
		vs_itoa_fd(vm->vs->fd, tmp->code_size);
		vs_putstr_fd(vm->vs->fd, "\n\t\t}");
		tmp = tmp->next;
		tmp != NULL ? vs_putstr_fd(vm->vs->fd, ",") : 1;
	}
	vs_putstr_fd(vm->vs->fd, "]\n\t},");
}

void	put_file(t_vm *vm, int type)
{
	type == 0 ? vs_putstr_fd(vm->vs->fd, "[{") :
	vs_putstr_fd(vm->vs->fd, ",{");
	if (type == 0)
	{
		put_atom_const(vm);
		put_array_const(vm);
	}
	vs_putstr_fd(vm->vs->fd, A_CYCLE);
	vs_itoa_fd(vm->vs->fd, vm->data->cycles);
	if(put_state(vm) == 0)
	{
		return ;
	}
	put_players(vm);
	put_carriages(vm);
	put_cells(vm);
	type == 2 ? vs_putstr_fd(vm->vs->fd, "\n}]")
	: vs_putstr_fd(vm->vs->fd, "\n}");
}

int		print_vsconst(t_vm	*vm, int type)
{
	char	*buf;
	int		buf_size;

	if (!vm->mods->vs)
		return (0);
	if (type == 0 &&
	(vm->vs->fd = open("vis.json", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
	{
		ft_dprintf(vm->vs->fd, "%s\n", "vis.json file error\n");
		return (0);
	}
	if (vm->vs->fd > 0)
	{
		put_file(vm, type);
		if (type == 2)
		{
			write(vm->vs->fd, "]", 1);
			close(vm->vs->fd);
			return (1);
		}
	}
	return (1);
}
