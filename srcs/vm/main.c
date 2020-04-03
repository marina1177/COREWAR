#include "../../includes/vm.h"

void	make_operation(t_vm *data, t_carriage *carriage, unsigned char *arguments)
{
	if (g_op_tab[(int)carriage->op_code].args_types_code)
		actions[(int)carriage->op_code](carriage, data, arguments);
	else
		actions[(int)carriage->op_code](carriage, data);
	printf("arguments is OK\n");
}

void	play_game(t_vm *data)
{
	t_carriage *carriage;
	unsigned char arguments[4];

	test(2, data->arena);
	carriage = data->carriages;
	while (carriage)
	{
		if (check_operation(data->arena, carriage, arguments))
			make_operation(data, carriage, arguments);
		carriage = carriage->next;
	}
}

int main(int ac, char **av)
{
	t_vm	data;
	int i;

	i = 0;
	init(&data, ac - 1);
	while(i < ac - 1)
	{
		read_data(av[i + 1], &data.players[i]); //заменить на функцию Димы
		i++;
	}
	init_arena(&data, ac - 1);
	play_game(&data);
	// printf("main arena\n\n");
	// print_memory(data.arena, MEM_SIZE);
	clean_data(&data);
	return 0;
}