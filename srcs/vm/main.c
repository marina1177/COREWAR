#include "../../includes/vm.h"

void	make_operation(t_vm *data, t_carriage *carriage, char *arguments)
{
	if (g_op_tab[carriage->op_code].args_types_code)
		actions[carriage->op_code](carriage, data->arena, arguments);
	else
		actions[carriage->op_code](carriage, data);
	printf("arguments is OK\n");
}

int			get_num_from_char(char *arena, int position, int size)
{
	int		*num;
	int		i;
	char	arguments[5];

	i = size;
	ft_bzero(arguments, 5);
	while (--i >= 0)
	{
		arguments[i] = arena[position];
		change_position(&position, 1);
	}
	print_memory(arguments, size);
	num = (int *)arguments;
	return (*num);
}

void	play_game(t_vm *data)
{
	t_carriage *carriage;
	unsigned char arguments[4];
	char check[100];
	ft_bzero(check, 100);
	char *try;
	try = ft_memcpy(check, data->arena, 50);
	check[0] = 2;
	check[1] = 0b10010111;
	data->arena[0] = 2;
	data->arena[1] = 0b11010111;
	data->arena[2] = 0;
	data->arena[3] = 5;
	data->arena[4] = 3;
	data->arena[5] = 0;
	data->arena[6] = 8;
	data->arena[7] = 5;
	data->arena[8] = 2;
	data->arena[9] = 55;
	print_memory(data->arena, 16);
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