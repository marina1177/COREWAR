#include "../includes/vm.h"

int		handle_error(char *s)
{	
	dprintf(2, "%s", s);
	exit(1);
}

int		handle_error_vm(char *error_message, t_vm *vm)
{	
	dprintf(2, "%s", error_message);
	exit(1);
}