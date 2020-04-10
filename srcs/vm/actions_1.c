#include "../../includes/vm.h"

void	do_live(t_carriage *carriage, t_vm *vm)
{
	int position;
	int num;
	int i;
	t_player *p;

	p = vm->players->first_player;
	i = 0;
	position = carriage->pos;
	carriage->last_cycle_alive = vm->data->cycles;
	change_position(&position, 2);
	num = get_arg_value(vm->data->arena, carriage, &position, T_DIR);
	if (num > 0 && num <= vm->players->qty)
	{
		while (++i <= vm->players->qty)
		{
	 		if (-num == p->num)
	 		{
	 			p->last_live = vm->data->cycles; //мы эту переменную увеличиваем?
	 			break ;
	 		}
	 		p = p->next;
	 	}
	}
	//TO DO разобраться со структурой Димы
	printf("live\n");
}

void	do_ld(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	int position;

	//printf("ld\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[1]] = values[0];
	carriage->carry = values[0] == 0 ? 1 : 0;
	carriage->pos = position;
	//printf("result reg[%d] = %d stay at %d\n",values[1], carriage->regs[values[1]], carriage->pos);
	//print_memory(&vm->data->arena[carriage->pos], 2);
}

void	do_st(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[2];
	int position;

	position = carriage->pos;	
	change_position(&position, 2);
	
	// printf("position %d\n", position);
	// print_memory(&vm->data->arena[carriage->pos], 8);
	//print_dump(vm, 32);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	//print_memory(&values[0], 4);
	// printf("каретка 01 = %d\n", carriage->regs[1]);
	
	if (arguments[1] == T_REG)
	{
		
		carriage->regs[get_reg_value(vm->data->arena, &position)] = values[0];
	}
	else
	{
		values[1] = get_num_from_char(vm->data->arena, position, 2) % IDX_MOD;
		write_reg(vm->data->arena, values[0], carriage->pos, values[1]); //нужно ли здесь дополнительно усекать?
	}
	carriage->pos = position;	
	//print_memory(vm->data->arena, 16);
	//printf("expect arena[%d] changed stay at %d\n", values[1], position);
}

void	do_add(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	//printf("add\n");
	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] + values[1]; //зачем здесь уменьшать?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
}

void	do_sub(t_carriage *carriage, t_vm *vm, unsigned char *arguments)
{
	int values[3];
	int position;

	position = carriage->pos;
	change_position(&position, 2);
	values[0] = get_arg_value(vm->data->arena, carriage, &position, arguments[0]);
	values[1] = get_arg_value(vm->data->arena, carriage, &position, arguments[1]);
	values[2] = get_reg_value(vm->data->arena, &position);
	carriage->regs[values[2]] = values[0] - values[1]; //зачем здесь уменьшать ?
	carriage->carry = carriage->regs[values[2]] == 0 ? 1 : 0;
	carriage->pos = position;
	// printf("sub\n");
	// printf("values[0] = %d values[1] = %d\n", values[0], values[1]);
	// printf("reg = %d\n", carriage->regs[3]);
	// print_memory(&vm->data->arena[carriage->pos], 1);
}
