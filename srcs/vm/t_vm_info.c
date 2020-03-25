#include "../../includes/vm.h"

t_vm_info *t_vm_info_new(void)
{
	t_vm_info	*new;

	new = (t_vm_info *)malloc(sizeof(t_vm_info));
	if (new)
	{
		new->cycles = 0;
		new->cycles_to_die = 0;
		new->checks_num = 0;
		new->cycles_after_check = 0;
		new->checks_counter = 0;
	}
	return (new);
}