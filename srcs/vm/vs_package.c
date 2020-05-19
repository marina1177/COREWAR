#include "../../includes/vm.h"

char	*put_atom_const(t_vm *vm, char **buf)
{
	char	*p;

	p = *buf;
	p += vs_strcpy(p,"\n\t\"Consts\": {\n\t\t\"mem_size\": ");
	p += vs_itoa(MEM_SIZE, p);
	p += vs_strcpy(p, A_CYCLEDELTA);
	p += vs_itoa(CYCLE_DELTA, p);
	p += vs_strcpy(p, A_PLAYERS_NUM);
	p += vs_itoa(vm->players->qty, p);
	p += vs_strcpy(p, A_MAXCHECKS);
	p += vs_itoa(MAX_CHECKS, p);
	p += vs_strcpy(p, A_C_NBR_LIVE);
	p += vs_itoa(NBR_LIVE, p);
	p += vs_strcpy(p, A_C_CYCLE_TO_DIE);
	p += vs_itoa(CYCLE_TO_DIE, p);
	return (p);
}

char	*put_array_const(t_vm *vm, char **buf)
{
	char	*p;
	t_player *tmp;

	p = *buf;
	p += vs_strcpy(p,",\n\t\t\"Players\": [");
	tmp = vm->players->first_player;
	while(tmp)
	{
		p += vs_strcpy(p, "\n\t\t{");
		p += vs_strcpy(p, A_C_ID);
		p += vs_itoa(tmp->num, p);
		p += vs_strcpy(p, A_NAME);
		*p++ = '\"';
		p += vs_strcpy(p, tmp->name);
		*p++ = '\"';
		p += vs_strcpy(p, A_START_CODE);
		p += vs_itoa(tmp->start_code, p);
		p += vs_strcpy(p, A_CODE_SIZE);
		p += vs_itoa(tmp->code_size, p);
		p += vs_strcpy(p, "\n\t\t}");
		tmp = tmp->next;
		tmp != NULL ? *p++ = ',' : 1;
	}
	p += vs_strcpy(p, "]\n\t},");
	return (p);
}

void	put_buf(t_vm *vm, int type, char **buf)
{
	char	*p;

	p = *buf;
	p += vs_strcpy(p,"[{");
	if (type == 0)
	{
		p = put_atom_const(vm, &p);
		p = put_array_const(vm, &p);
	}
	p += vs_strcpy(p, A_CYCLE);
	p += vs_itoa(vm->data->cycles, p);
	if((p = put_state(vm, &p)) == NULL)
	{
		return ;
	}
	p = put_players(vm, &p);
	p = put_carriages(vm, &p);
	p = put_cells(vm, &p);
	p += vs_strcpy(p,"\n}]");
	printf("VS_COMM:(%ld[ch])\n", (p-*buf));
}

void	print_vsconst(t_vm	*vm, int type)
{
	char	*buf;
	int		buf_size;

	buf_size = calculate_buf(vm, type);
	if ((buf = (char *)malloc(buf_size)))
	{
		ft_bzero(buf, buf_size);
		put_buf(vm, type, &buf);
		ft_dprintf(1, "%s\n", buf);
		free(buf);
	}
	else
		handle_error_vm(ERR_ALLOC, vm);

}

