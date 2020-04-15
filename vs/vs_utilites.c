#include "../../includes/vm.h"

int		count_dig(size_t val)
{
	int		i;
	size_t	n;

	i = 0;
	n = val;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	printf("count_dig: val = %zu  i = %d\n", val, i);
	return (i);
}

int		vs_putstr_fd(char const *s, int fd)
{
	size_t i;

	if (!s || !*s)
		return (0);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}

int		vs_strcpy(char *dest, const char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = dest;
	while (*src)
	{
		*(temp++) = *(src++);
		i++;
	}
	*temp = '\0';
	return (i);
}

uint64_t	calculate_buf(t_vm *vm, int type)
{
	uint64_t	buff_size;
	t_cells		*tmp;

	buff_size = 0;
	if (type == 0)
		buff_size += vm->vs->const_begin_len + 6 * 15 + (3 * 15 + 128 + 20) * vm->players->qty + 30;
	buff_size += (vm->vs->change_begin_len) + 30;
	if (vm->vs->state_refresh > 0 && vm->vs->error_code == 0)
		buff_size += 5 + 3 * 15;
	else if ( vm->vs->error_code > 0)
		return (buff_size);
	if (vm->vs->players_refresh > 0)
		buff_size += vm->players->qty * (1 + 3 * 15 + 20);
	if (vm->vs->cells_refresh > 0)
		buff_size += vm->carr->qty * (15 * 3 + 20);
	tmp = vm->cells;
	while (tmp)
	{
		buff_size += tmp->num_addr * 15 + 15 + 20;
		tmp = tmp->next;
	}
	printf("buff_size = %lu\n", buff_size);
	return (buff_size);
}
