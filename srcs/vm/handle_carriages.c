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



# define ARGS_ARR_SIZE 4


static void	get_op_code(t_carriage *carriage, t_vm *vm)
{
	carriage->op_code = vm->data->arena[carriage->pos];
	if (vm->data->arena[carriage->pos] & 0b10000000)
		carriage->op_code = get_negative_number(&vm->data->arena[carriage->pos], 1);
	//ft_printf("%d car pos %d car num\n", carriage->pos, carriage->num - 1);
	carriage->cycles_countdown = 1;
	if (carriage->op_code >= 0x01 && carriage->op_code <= 0x10)
		carriage->cycles_countdown = (vm->op_tab)[carriage->op_code].loop;
}

/*
** Remastered, may not work
*/
void			handle_carriages(t_vm *vm)
{
	t_carriage	*carriage;
	unsigned char arguments[4];	

	carriage = vm->carr->head;
	while (carriage)
	{
		carriage->cycles_countdown < 0 ? get_op_code(carriage, vm) : 0;
		if (vm->mods->dump_cycle - vm->data->cycles <  CYCLES_BEFORE_DUMP)
		{
			//ft_printf("cycle %d, carriage %d, op_code %d, car pos %d, cd %d, last_cycle_alive %d\n",
		//vm->data->cycles, carriage->num - 1, carriage->op_code, carriage->pos, carriage->cycles_countdown, carriage->last_cycle_alive);
		//	print_t_carriage(carriage);
		}
			if (vm->data->cycles > 0 && carriage->cycles_countdown >= 0)
			{
				carriage->cycles_countdown--;
				if (!carriage->cycles_countdown)
				{
					if (check_operation(vm->data->arena, carriage, arguments))
					{						
						make_operation(vm, carriage, arguments);
					}
					carriage->cycles_countdown--;					
				}
			}
				
		carriage = carriage->next;
	}
	//if (vm->mods->dump_cycle - vm->data->cycles <  CYCLES_BEFORE_DUMP)
	//	ft_putchar('\n');
}