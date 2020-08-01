/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:13:26 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 11:21:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			handle_error(char *s)
{
	ft_dprintf(2, "%s %s\n", s);
	exit(1);
}

int			error_op_h(char *def_name, int prop_val)
{
	ft_dprintf(2,
			"%s Invalid %s size. The value must be equal to %d\n",
			ERROR_WORD, def_name, prop_val);
	exit(1);
}

int			error_range_op_h(char *def_name, int min_val, int max_val)
{
	ft_dprintf(2,
			"%s Invalid %s size. The value must be in range [%d, %d]\n",
			ERROR_WORD, def_name, min_val, max_val);
	exit(1);
}

int			handle_error_vm(char *error_message, t_vm *vm)
{
	ft_dprintf(2, "%s %s\n", ERROR_WORD, error_message);
	vs_print_error(vm, error_message);
	t_vm_free(vm);
	exit(1);
}

int			handle_error_str_arg(char *error_message, char *arg, t_vm *vm)
{
	char	*s;

	ft_asprintf(&s, error_message, arg);
	ft_dprintf(2, "%s %s\n", ERROR_WORD, s);
	vs_print_error(vm, error_message);
	free(s);
	t_vm_free(vm);
	exit(1);
}
