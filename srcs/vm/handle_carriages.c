/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/05/11 21:56:47 by clala            ###   ########lyon.fr   */
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

void				increase_position(int *pos, int delta)
{
	*pos += delta;
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	else if (*pos < 0)
		*pos += MEM_SIZE;
}

static void			get_op_code(t_carriage *carriage, t_vm *vm)
{
	carriage->op_code = (int)vm->data->arena[carriage->pos];
	carriage->cycles_countdown = 1;
	if (carriage->op_code >= 1 && carriage->op_code <= 16)
		carriage->cycles_countdown = (vm->op_tab)[carriage->op_code].loop;
	vs_carriages_refresh(vm);
}

void				handle_carriages(t_vm *vm)
{
	t_carriage		*carriage;
	unsigned char	arguments[4];
	int				temp_print_pos;
	int				temp_vs_pos;

	carriage = vm->carr->head;
	/*
	if (vm->data->cycles > 3827)
	{
		printf("302 val %d\n", vm->data->arena[302]);
		print_t_carriages(vm->carr);
	}
	*/
	while (carriage)
	{		
		temp_vs_pos = carriage->pos;
		carriage->cycles_countdown < 0 ? get_op_code(carriage, vm) : 0;
		//if (carriage->num == 24)
		//	print_t_carriage(carriage);
		if (vm->data->cycles > 0 && carriage->cycles_countdown > 0)
			carriage->cycles_countdown--;
		if (vm->data->cycles > 0 && carriage->cycles_countdown == 0)
		{
			temp_print_pos = carriage->pos;			
			if (check_operation(vm->data->arena, carriage, arguments))
			{							
				make_operation(vm, carriage, arguments);									
			}
			print_move(vm, carriage, temp_print_pos);
			carriage->cycles_countdown = -1;
		}
		carriage->pos == temp_vs_pos ? 0 : vs_carriages_refresh(vm);
		carriage = carriage->next;
	}
	
}
