#include "../../includes/vm.h"

#define INT_SIZE 4

void		live(t_carriage *curr, t_vm *vm)
{
	int		temp;
	int		num;
	t_player	*player;

	curr->last_cycle_alive = vm->data->cycles;
	num = 0;
	temp = curr->pos;
	increase_position(&temp, 1);
	num = get_int(&temp, curr, vm, INT_SIZE);
	if (-num <= vm->players->qty && -num >= 1)
	{
		vm->players->last_alive_num = -num;
		if (vm->mods->dump_cycle)
		{
			player = get_player_by_number(vm->players, -num);
			print_is_alive(-num, player->name);
		}			
	}
	vm->data->lives_counter++;
}

void		ld(t_carriage *curr, t_vm *vm)
{
	int				temp;
	unsigned char	args[4];
	int				num;

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);	
	num = get_one_arg(&temp, args[0], curr, vm);
	temp = curr->pos;
	if (args[0] == 2)
		increase_position(&temp, 6);
	else
		increase_position(&temp, 4);
	curr->regs[vm->data->arena[temp] - 1] = num;
	curr->carry = num == 0 ? 1 : 0;
}

void		st(t_carriage *curr, t_vm *vm)
{
	int		num;
	int		temp;
	unsigned char	args[4];

	temp = curr->pos;
	increase_position(&temp, 1);
	get_args(vm->data->arena[temp], args);
	increase_position(&temp, 1);	
	num = curr->regs[vm->data->arena[temp] - 1];
	increase_position(&temp, 1);
	if (args[1] == 1)
		curr->regs[vm->data->arena[temp] - 1] = num;
	else
	{
		temp = curr->pos +
					get_int(&temp, curr, vm, 2) % IDX_MOD;
		set_int(&temp, num, vm);
	}
}

void		add(t_carriage *curr, t_vm *vm)
{
	int		temp;
	int		num[2];

	temp = curr->pos;
	increase_position(&temp, 2);
	num[0] = vm->data->arena[temp];
	increase_position(&temp, 1);
	num[1] = vm->data->arena[temp];
	increase_position(&temp, 1);
	curr->regs[vm->data->arena[temp] - 1] = \
		 curr->regs[num[0] - 1] + curr->regs[num[1] - 1];
	curr->carry = curr->regs[vm->data->arena[temp] - 1] == 0 ? 1 : 0;
}