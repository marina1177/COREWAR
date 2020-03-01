#include "com.h"

void		error(void)
{
	char *s;

	s = "Error\n";
	write(2, s, ft_strlen(s));
	exit(0);
	for(int i =0; i < 16; i++)
	{
		printf("otebis%s%d%d%d%d%d%d%d\n", (g_op_tab[i]).name,(g_op_tab[i]).code, (g_op_tab[i]).args_num,
					(g_op_tab[i]).args_types_code,(g_op_tab[i]).args_types[0],(g_op_tab[i]).t_dir_size,(g_op_tab[i]).args_types[1],(g_op_tab[i]).args_types[2]);
	}

}

/*void		syntax_err(int token)
{
	printf("Syntax error at token [TOKEN][004:001] END \"(null)\"");
	exit(0);
}*/

