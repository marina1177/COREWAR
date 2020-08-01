/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 11:21:29 by clala             #+#    #+#             */
/*   Updated: 2020/08/01 12:42:34 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			handle_error_int_arg(char *error_message, int arg, t_vm *vm)
{
	char	*s;

	ft_asprintf(&s, error_message, arg);
	ft_dprintf(2, "%s %s\n", ERROR_WORD, s);
	vs_print_error(vm, error_message);
	free(s);
	t_vm_free(vm);
	exit(1);
	return (1);
}

int			print_usage(void)
{
	ft_printf("Usage: ./corewar [-d N -v N] [-a] <champion.cor> <...>\n");
	ft_printf("    %-11s : Python visualization\n", "-vs");
	ft_printf("    %-11s : Print output from \"aff\" (Default is off)\n", "-a");
	ft_printf("    %-11s : Print carriages info every cycle. ", "-pc");
	ft_printf("With -d / -dump flags prints carriages only at dump cycle\n");
	ft_printf("    %-11s : Dump memory (32 octets per line)"\
							" after <num> cycles and exit\n", "-dump <num>");
	ft_printf("    %-11s : Dump memory (64 octets per line)"\
							" after <num> cycles and exit\n", "-d    <num>");
	ft_printf("    %-11s : Verbosity levels\n", "-v    <num>");
	ft_printf("            %9s : Essential output\n", "0 ");
	ft_printf("            %9s : Show lives\n", "1 ");
	ft_printf("            %9s : Show cycles\n", "2 ");
	ft_printf("            %9s : Show operations\n", "4 ");
	ft_printf("            %9s : Show deaths\n", "8 ");
	ft_printf("            %9s : Show PC movements\n", "16");
	ft_printf("    %-11s : Set <num> of the next player\n", "-n    <num>");
	exit(0);
}
