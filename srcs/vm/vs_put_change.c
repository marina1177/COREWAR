/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_put_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 23:06:51 by clala             #+#    #+#             */
/*   Updated: 2020/07/04 23:06:52 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"


void	put_cells(t_vm *vm)
{
	t_cells	*tmp;
	int		num;

	vs_putstr_fd(vm->vs->fd, A_CELLS_REF);
	vs_itoa_fd(vm->vs->fd, vm->vs->cells_refresh);
	if (vm->vs->cells_refresh > 0)
	{
		vs_putstr_fd(vm->vs->fd, ",\n\t\"Cells\": [");
		tmp = vm->cells;
		while(tmp)
		{
			vs_putstr_fd(vm->vs->fd, "\n\t\t{");
			vs_putstr_fd(vm->vs->fd, A_ID);
			vs_itoa_fd(vm->vs->fd, tmp->players_id);
			vs_putstr_fd(vm->vs->fd, ",\n\t\t\"cells_address\": [");
			num = tmp->num_addr;
			while (num >= 0)
			{
				vs_itoa_fd(vm->vs->fd, tmp->cells_address[num]);
				num != 0 ? vs_putstr_fd(vm->vs->fd, ",") : 1;
				num--;
			}
			vs_putstr_fd(vm->vs->fd, "]\n\t}");
			tmp = tmp->next;
			tmp != NULL ? vs_putstr_fd(vm->vs->fd, ",") : 1;
		}
		vs_putstr_fd(vm->vs->fd, "]");
	}
}

void	put_carriages(t_vm *vm)
{
	t_carriage *tmp;

	vs_putstr_fd(vm->vs->fd,  A_CAR_REF);
	vs_itoa_fd(vm->vs->fd, vm->vs->carriages_refresh);
	vs_putstr_fd(vm->vs->fd, ",");
	if (vm->vs->carriages_refresh > 0)
	{
		vs_putstr_fd(vm->vs->fd, "\n\t\"Carriages\": [");
		tmp = vm->carr->head;
		while(tmp)
		{
			vs_putstr_fd(vm->vs->fd, "\n\t\t{");
			vs_putstr_fd(vm->vs->fd, A_ID);
			vs_itoa_fd(vm->vs->fd, tmp->num);
			vs_putstr_fd(vm->vs->fd, A_OP_CODE);
			vs_itoa_fd(vm->vs->fd, tmp->op_code);
			vs_putstr_fd(vm->vs->fd, A_PLACE);
			vs_itoa_fd(vm->vs->fd, tmp->pos);
			vs_putstr_fd(vm->vs->fd, "\n\t\t}");
			tmp = tmp->next;
			tmp != NULL ? vs_putstr_fd(vm->vs->fd, ",") : 1;
		}
		vs_putstr_fd(vm->vs->fd, "],");
	}
}

void	put_players(t_vm *vm)
{
	t_player *tmp;

	vs_putstr_fd(vm->vs->fd,  A_PLAYERS_REF);
	vs_itoa_fd(vm->vs->fd, vm->vs->players_refresh);
	vs_putstr_fd(vm->vs->fd, ",");
	if (vm->vs->players_refresh > 0)
	{
		vs_putstr_fd(vm->vs->fd, "\n\t\"Players\": [");
		tmp = vm->players->first_player;
		while(tmp)
		{
			vs_putstr_fd(vm->vs->fd, "\n\t\t{");
			vs_putstr_fd(vm->vs->fd, A_ID);
			vs_itoa_fd(vm->vs->fd, tmp->num);
			vs_putstr_fd(vm->vs->fd, A_IS_ALIVE);
			vs_itoa_fd(vm->vs->fd, tmp->is_alive);
			vs_putstr_fd(vm->vs->fd, A_LAST_LIVE);
			vs_itoa_fd(vm->vs->fd, tmp->last_live);
			vs_putstr_fd(vm->vs->fd, A_LPP);
			vs_itoa_fd(vm->vs->fd, tmp->lives_in_period);//добавить lives_num  в players
			vs_putstr_fd(vm->vs->fd, "\n\t\t}");
			tmp = tmp->next;
			tmp != NULL ? vs_putstr_fd(vm->vs->fd, ",") : 1;
		}
		vs_putstr_fd(vm->vs->fd, "],");
	}
}

int		put_state(t_vm *vm)
{
	vs_putstr_fd(vm->vs->fd, A_STATE_REF);
	vs_itoa_fd(vm->vs->fd, vm->vs->state_refresh);
	vs_putstr_fd(vm->vs->fd, ",");
	if (vm->vs->state_refresh > 0)
	{
		vs_putstr_fd(vm->vs->fd, "\n\t\"State\": {\n\t\t\"error_code\": ");
		vs_itoa_fd(vm->vs->fd, vm->vs->error_code);
		if (vm->vs->error_code > 0)
		{
			vs_putstr_fd(vm->vs->fd, "\n\t}\n}]");
			return (0);
		}
		vs_putstr_fd(vm->vs->fd, A_TOTAL_PROC);
		vs_itoa_fd(vm->vs->fd, vm->carr->qty);
		vs_putstr_fd(vm->vs->fd, A_CYCLE_TO_DIE);
		vs_itoa_fd(vm->vs->fd, vm->data->cycles_to_die);
		vs_putstr_fd(vm->vs->fd, A_NBR_LIVE);
		vs_itoa_fd(vm->vs->fd, vm->data->lives_counter);
		vs_putstr_fd(vm->vs->fd, "\n\t},");
	}
	return (1);
}
