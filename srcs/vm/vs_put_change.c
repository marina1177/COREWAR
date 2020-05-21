#include "../../includes/vm.h"


char	*put_cells(t_vm *vm, char **buf)
{
	char	*p;
	t_cells *tmp;

	p = *buf;
	p += vs_strcpy(p, A_CELLS_REF);
	p += vs_itoa(vm->vs->cells_refresh, p);
	if (vm->vs->cells_refresh > 0)
	{
		p += vs_strcpy(p,",\n\t\"Cells\": [");
		tmp = vm->cells;
		while(tmp)
		{			
			p += vs_strcpy(p, "\n\t\t{");
			p += vs_strcpy(p, A_ID);
			p += vs_itoa(tmp->players_id, p);
			p += vs_strcpy(p,",\n\t\t\"cells_address\": [");
			int num;
			num = tmp->num_addr;
			while (num-- > 0)
			{
				p += vs_itoa(tmp->cells_address[num], p);
				num != 0 ? *p++ = ',' : 1;
			}
			p += vs_strcpy(p, "]\n\t}");
			tmp = tmp->next;
			tmp != NULL ? *p++ = ',' : 1;
		}
		p += vs_strcpy(p, "]");
	}
	return (p);
}


char	*put_carriages(t_vm *vm, char **buf)
{
	char	*p;
	t_carriage *tmp;

	p = *buf;
	p += vs_strcpy(p, A_CAR_REF);
	p += vs_itoa(vm->vs->carriages_refresh, p);
	p += vs_strcpy(p, ",");
	if (vm->vs->carriages_refresh > 0)
	{
		p += vs_strcpy(p,"\n\t\"Carriages\": [");
		tmp = vm->carr->head;
		while(tmp)
		{
			p += vs_strcpy(p, "\n\t\t{");
			p += vs_strcpy(p, A_ID);
			p += vs_itoa(tmp->num, p);
			p += vs_strcpy(p, A_OP_CODE);
			p += vs_itoa(tmp->op_code, p);
			p += vs_strcpy(p, A_PLACE);
			p += vs_itoa(tmp->pos, p);
			p += vs_strcpy(p, "\n\t\t}");
			tmp = tmp->next;
			tmp != NULL ? *p++ = ',' : 1;
		}
		p += vs_strcpy(p, "],");
	}
	return (p);
}

char	*put_players(t_vm *vm, char **buf)
{
	char	*p;
	t_player *tmp;

	p = *buf;
	p += vs_strcpy(p, A_PLAYERS_REF);
	p += vs_itoa(vm->vs->players_refresh, p);
	p += vs_strcpy(p, ",");
	if (vm->vs->players_refresh > 0)
	{
		p += vs_strcpy(p,"\n\t\"Players\": [");
		tmp = vm->players->first_player;
		while(tmp)
		{
			p += vs_strcpy(p, "\n\t\t{");
			p += vs_strcpy(p, A_ID);
			p += vs_itoa(tmp->num, p);
			p += vs_strcpy(p, A_IS_ALIVE);
			p += vs_itoa(tmp->is_alive, p);
			p += vs_strcpy(p, A_LAST_LIVE);
			p += vs_itoa(tmp->last_live, p);
			p += vs_strcpy(p, A_LPP);
			p += vs_itoa(tmp->lives_in_period, p);//добавить lives_num  в players
			p += vs_strcpy(p, "\n\t\t}");
			tmp = tmp->next;
			tmp != NULL ? *p++ = ',' : 1;
		}
		p += vs_strcpy(p, "],");
	}
	return (p);
}

char	*put_state(t_vm *vm, char **buf)
{
	char	*p;

	p = *buf;
	p += vs_strcpy(p, A_STATE_REF);
	p += vs_itoa(vm->vs->state_refresh, p);
	p += vs_strcpy(p, ",");
	if (vm->vs->state_refresh > 0)
	{		
		p += vs_strcpy(p,"\n\t\"State\": {\n\t\t\"error_code\": ");
		p += vs_itoa(vm->vs->error_code, p);
		if (vm->vs->error_code > 0)
		{
			p += vs_strcpy(p,"\n\t}\n}]");
			return (NULL);
		}
		p += vs_strcpy(p, A_TOTAL_PROC);
		p += vs_itoa(vm->carr->qty, p);
		p += vs_strcpy(p, A_CYCLE_TO_DIE);
		p += vs_itoa(vm->data->cycles_to_die, p);
		p += vs_strcpy(p, A_NBR_LIVE);
		p += vs_itoa(vm->data->lives_counter, p);
		p += vs_strcpy(p, "\n\t},");
	}
	return (p);
}
