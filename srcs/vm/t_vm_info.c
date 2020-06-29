/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vm_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/05/11 21:56:47 by clala            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static t_vm_info	*t_vm_info_new(void)
{
	t_vm_info		*new;

	new = (t_vm_info *)malloc(sizeof(t_vm_info));
	if (new)
	{
		new->cycles = 0;
		new->cycles_to_die = CYCLE_TO_DIE;
		new->checks_num = 0;
		new->cycles_after_check = 0;
		new->checks_counter = 0;
		new->lives_counter = 0;
	}
	return (new);
}

t_vm_info			*t_vm_info_create(t_vm *vm)
{
	t_vm_info		*new;

	new = t_vm_info_new();
	if (!new)
		handle_error_vm(ERR_ALLOC, vm);
	vm->allocated += ALLOCATED_DATA;
	ft_memset(new->arena, 0, MEM_SIZE);
	return (new);
}
