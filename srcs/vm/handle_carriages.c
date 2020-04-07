/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 18:04:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"



unsigned char		*get_args(char arg_code, unsigned char arr[4])
{
	arr[0] = (arg_code & 0b10000000) >> 6;
	arr[0] |= (arg_code & 0b01000000) >> 6;
	arr[1] = (arg_code & 0b00100000) >> 4;
	arr[1] |= (arg_code & 0b00010000) >> 4;
	arr[2] = (arg_code & 0b00001000) >> 2;
	arr[2] |= (arg_code & 0b00000100) >> 2;
	arr[3] = arg_code & 0b00000010;
	arr[3] |= arg_code & 0b00000001;
	return (arr);
}

void			increase_position(int *pos, int delta)
{
	*pos += delta;
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	else if (*pos < 0)
		*pos += MEM_SIZE;
}


static int		check_reg(unsigned char *args, t_carriage *curr,
							t_vm *vm)
{
	int				i;
	int				temp;

	i = 0;
	temp = curr->pos;
	increase_position(&temp, 2);
	while (i < (vm->op_tab)[curr->opcode].arg_count)
	{
		if (args[i] == 0x2 && (vm->op_tab)[curr->opcode].dir_size)
			increase_position(&temp, 2);
		else if (args[i] == 0x2 &&
				!((vm->op_tab)[curr->opcode].dir_size))
			increase_position(&temp, 4);
		else if (args[i] == 0x3)
			increase_position(&temp, 2);
		else if (args[i] == 0x01)
		{
			if (vm->data->arena[temp] < 0x01 ||
				vm->data->arena[temp] > REG_NUMBER) //REG_NUMBER_VM
				return (0);
			increase_position(&temp, 2);
		}
		i++;
	}
	return (1);
}

static int		size_of_step(unsigned char *args, int size, int tdir_size)
{
	int		i;
	int		step;

	i = 0;
	if (size == 0)
		size = 3;
	step = 2;
	while (i < size)
	{
		if (args[i] == 0x1)
			step += 1;
		else if ((args[i] == 0x2 && tdir_size) || args[i] == 0x3)
			step += 2;
		else if (args[i] == 0x2 && !tdir_size)
			step += 4;
		i++;
	}
	return (step);
}

int				is_args_valid(int *step, unsigned char *args, t_carriage *curr,
							t_vm *vm)
{
	int		correct;
	int		i;
	int		*arr;

	i = 0;
	arr = (vm->op_tab)[curr->opcode].arr;
	correct = 1;
	while (i < (vm->op_tab)[curr->opcode].arg_count)
	{
		if ((arr[i] == 7 && args[i] == 0x0) ||
			(arr[i] == 6 && (args[i] != 0x2 && args[i] != 0x3)) ||
			(arr[i] == 5 && (args[i] != 0x1 && args[i] != 0x3)) ||
			(arr[i] == 3 && (args[i] != 0x1 && args[i] != 0x2)) ||
			(arr[i] == 2 && args[i] != 0x2) ||
			(arr[i] == 1 && args[i] != 0x1))
		{
			correct = 0;
			break ;
		}
		i++;
	}
	correct = !correct ? 0 : check_reg(args, curr, vm);
	*step = size_of_step(args, (vm->op_tab)[curr->opcode].arg_count,
						(vm->op_tab)[curr->opcode].dir_size);
	return (correct);
}

# define ARGS_ARR_SIZE 4
static int	is_code_valid(int *i, t_carriage *carriage, t_vm *vm)
{
	int				pos;
	unsigned char	args[ARGS_ARR_SIZE];
	
	if ((vm->op_tab[carriage->opcode].arg_type))
	{
		pos = carriage->pos;
		increase_position(&pos, 1);
		get_args(vm->data->arena[pos], args);
		if (!is_args_valid(i, args, carriage, vm))
			return (0);
	}
	else if (carriage->opcode == 1)
		*i = 5;
	else
		*i = 3;
	return (1);
}

int		exec_op(t_carriage *carriage, t_vm *vm)
{
	int	i;


	if (carriage->opcode >= 0x01 && carriage->opcode <= 0x10)
	{
		if (is_code_valid(&i, carriage, vm))
		{
			(vm->exec)[carriage->opcode](carriage, vm);
		}
		if (carriage->opcode != 0x09 ||
			(carriage->opcode == 0x09 && !carriage->carry))
			increase_position(&(carriage->pos), i);
	}
	else
		increase_position(&(carriage->pos), 1);
	carriage->cycles_countdown = -1;
	return (1);
}

static int	get_opcode(t_carriage *carriage, t_vm *vm)
{
	carriage->opcode = (int)(vm->data->arena[carriage->pos]);
	carriage->cycles_countdown = 1;
	if (carriage->opcode >= 0x01 && carriage->opcode <= 0x10)
		carriage->cycles_countdown = (vm->op_tab)[carriage->opcode].loop;
	return (1);
}

/*
** Remastered, may not work
*/
void			handle_carriages(t_vm *vm)
{
	t_carriage	*carriage;
	/*char names[17][5] = {"0", "live", "ld", "st", "add", "sub", "and", "or",
						 "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"}; */

	carriage = vm->carr->head;
	while (carriage)
	{		
		carriage->cycles_countdown < 0 ? get_opcode(carriage, vm) : 0;
		if (vm->data->cycles > 0 && carriage->cycles_countdown >= 0)
		{
			carriage->cycles_countdown--;
			if (!carriage->cycles_countdown)
			{
				exec_op(carriage, vm);
				ft_printf("cycle: %d operation: %s\n", vm->data->cycles, names[carriage->opcode]);
			}
		}
		carriage = carriage->next;
	}
}