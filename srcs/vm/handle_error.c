#include "../../includes/vm.h"

int		handle_error(char *s)
{	
	ft_dprintf(2, "ERROR : %s\n", s);
	exit(1);
}

int		handle_error_vm(char *error_message, t_vm *vm)
{	
	ft_dprintf(2, "ERROR : %s\n", error_message);
	vm->players->qty++;
	exit(1);
}

int		handle_error_str_arg(char *error_message, char *arg, t_vm *vm)
{
	char *s;

	ft_asprintf(&s, error_message, arg);
	ft_dprintf(2, "ERROR : %s\n", s);
	vm->players->qty++;
	exit(1);
}

int		handle_error_int_arg(char *error_message, int arg, t_vm *vm)
{
	char *s;

	ft_asprintf(&s, error_message, arg);	
	ft_dprintf(2, "ERROR : %s\n", s);
	vm->players->qty++;
	exit(1);
}

int		print_usage(void)
{
	ft_printf("%sHello! There will be usage soon%s\n", C_GRN, C_NRM);
	/*
	ft_printf("Usage: ./corewar [-a (-dump|-d) <num> (-shed|-s) <num> -l"\
							" <num>] [-v] [-n <num>] <champion.cor> <...>\n");
	ft_printf("    %-11s : Print output from \"aff\" (Default is off)\n", "-a");
	ft_printf("    %-11s : Dump memory (32 octets per line)"\
							" after <num> cycles and exit\n", "-dump <num>");
	ft_printf("    %-11s : Dump memory (64 octets per line)"\
							" after <num> cycles and exit\n", "-d    <num>");
	ft_printf("    %-11s : Run <num> cycles, dump memory (32 octets per line),"\
							" pause and repeat\n", "-show <num>");
	ft_printf("    %-11s : Run <num> cycles, dump memory (64 octets per line),"\
							" pause and repeat\n", "-s    <num>");
	
	ft_printf("    %-11s : Log levels\n", "-l    <num>");
	ft_printf("            %9s : Show lives\n", "1 ");
	ft_printf("            %9s : Show cycles\n", "2 ");
	ft_printf("            %9s : Show operations\n", "4 ");
	ft_printf("            %9s : Show deaths\n", "8 ");
	ft_printf("            %9s : Show PC movements\n", "16");
	ft_printf("    %-11s : Run visualizer\n", "-v");
	ft_printf("    %-11s : Set <num> of the next player\n", "-n    <num>");
	*/

	exit (0);
}