#include "../../includes/vm.h"

t_vm_info *t_vm_info_new(void)
{
	t_vm_info	*new;

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

t_vm_info *t_vm_info_create(t_vm *vm)
{
	t_vm_info	*new;

	new = t_vm_info_new();
	if (!new)
		handle_error_vm(ERR_ALLOC, vm);
	ft_memset(new->arena, 0, MEM_SIZE);
	return (new);
}